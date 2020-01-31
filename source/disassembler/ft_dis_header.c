/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dis_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:32:07 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:32:08 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_g_com.h"
#include "../../includes/dis_asm.h"
#include <stdio.h>

unsigned int		ft_read_number(unsigned char *str, unsigned short int byte)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	if (byte > 4 || !str)
		return (0);
	while (i < byte)
	{
		res |= *(str + i) << (8 * (byte - i - 1));
		i++;
	}
	return (res);
}

void				ft_read_cor(t_data *data, char *str)
{
	unsigned char *tmp;
	size_t size;

	data->fd[0] = open(str, O_RDONLY);
	if (data->fd[0] <= 0)
		ft_error(0, 1);
	if ((data->fd[1] = open(data->file, O_WRONLY | O_CREAT | O_TRUNC, 0666))
		== -1)
		ft_error(0, 3);
	size = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	if (!(data->name = ft_memalloc(size + 1)))
		ft_error(0, 11);
	if (read(data->fd[0], data->name, size) < size)
		ft_error(0, 12);
	size = ft_read_number(data->name + PROG_NAME_LENGTH + 8, 4);
	data->lenght = size;
	if (!((data->command) = ft_memalloc(size + 1)))
		ft_error(0, 15);
	tmp = data->command;
	while ((size = read(data->fd[0], tmp, MAX_BUFFER)) > 0)
		tmp = tmp + size;
}


void		ft_dis_header(t_data *data)
{
	if (ft_read_number(data->name, 4) != COREWAR_EXEC_MAGIC)
		ft_error(0, 13);
	ft_putstr_fd(NAME_CMD_STRING ,data->fd[1]);
	write(data->fd[1], " \"", 2);
	write(data->fd[1], data->name + 4, ft_strlen((char *)(data->name + 4)));
	write(data->fd[1], "\"\n", 2);
	ft_putstr_fd(COMMENT_CMD_STRING, data->fd[1]);
	write(data->fd[1], " \"", 2);
	write(data->fd[1], data->name + 140, ft_strlen((char *)(data->name + 140)));
	write(data->fd[1], "\"\n\n", 3);
}
