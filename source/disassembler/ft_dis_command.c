/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dis_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:22:49 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/31 16:22:51 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_g_com.h"
#include "../../includes/dis_asm.h"
#include <stdio.h>

int			ft_find_com(t_data *data, unsigned char **tmp)
{
	int		res;

	while (g_com[res].n_com)
	{
		if (g_com[res].n_com == **tmp)
		{
			(*tmp)++;
			return (res);
		}
		res++;
	}
	return (-1);
}

void				ft_read_type(unsigned char **tmp, t_dcom *tk)
{
	int				i;

	i = 0;
	if (!g_com[tk->name].t_dec)
	{
		while (g_com[tk->name].arg[i])
		{
			if (g_com[tk->name].arg[i] == T_REG)
				tk->type[i] = REG_CODE;
			else if (g_com[tk->name].arg[i] == T_IND)
				tk->type[i] = IND_CODE;
			else if (g_com[tk->name].arg[i] == T_DIR)
				tk->type[i] = DIR_CODE;
			i++;
		}
		return ;
	}
	while ((**tmp & (3 << (6 - (i * 2)))))
	{
		tk->type[i] = **tmp & (3 << (6 - (i * 2)));
		tk->type[i] >>= (6 - (i * 2));
		i++;
	}
	(*tmp)++;
}

void				ft_write_arg(t_data *data, unsigned char **tmp, t_dcom *tk)
{
	int				i;
	int				num;

	i = 0;
	while (tk->type[i])
	{
		if (tk->type[i] == REG_CODE)
		{
			num = (char)ft_read_number(*tmp, REG_BYTE);
			(*tmp) += REG_BYTE;
			write(data->fd[1], "r", 1);
		}
		if (tk->type[i] == IND_CODE)
		{
			num = (short int)ft_read_number(*tmp, IND_SIZE);
			(*tmp) += IND_SIZE;
		}
		if (tk->type[i] == DIR_CODE)
		{
			if (g_com[tk->name].s_dir == 2)
				num = (short int)ft_read_number(*tmp, g_com[tk->name].s_dir);
			else
				num = (int)ft_read_number(*tmp, g_com[tk->name].s_dir);
			(*tmp) += g_com[tk->name].s_dir;
			write(data->fd[1], "%", 1);
		}
		ft_putnbr_fd(num, data->fd[1]);
		i++;
		if (tk->type[i])
			write(data->fd[1], ", ", 2);
	}
	write(data->fd[1], "\n", 1);
}

void				ft_dis_command(t_data *data)
{
	size_t	i;
	unsigned char	*tmp;
	t_dcom			token;

	i = 0;
	tmp = data->command;
	while (tmp < data->command + data->lenght)
	{
		ft_memset(&token, 0, sizeof(t_dcom));
		if ((token.name = ft_find_com(data, &tmp)) == -1)
			ft_error(0, 19);
		ft_putstr_fd(g_com[token.name].name, data->fd[1]);
		ft_putchar_fd(32, data->fd[1]);
		ft_read_type(&tmp, &token);
		ft_write_arg(data, &tmp, &token);
	}
}
