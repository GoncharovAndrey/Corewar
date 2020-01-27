/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:38:38 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/27 14:38:40 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	ft_check_name_command(char *str, t_op *com)
{
	int		i;
	int		res;

	i = 0;
	res = -1;
	while (com[i].n_com)
	{
		if (ft_strncmp(str, com[i].name, com[i].n_sym) == 0)
			res = i;
		i++;
	}
	return (res);
}

static void	ft_check_argument(char **str, t_op *com, t_root *root)
{
	int		j;

	j = 0;
	while (j < com->n_arg)
	{
		if (*str && **str == SEPARATOR_CHAR)
			(*str)++;
		while (*str && **str && (**str == 32 || **str == '\t'))
			(*str)++;
		if ((com->arg[j] & T_REG) && **str == REGISTOR_CHAR)
			ft_check_registor(str, root, com, j);
		else if ((com->arg[j] & T_DIR) && **str == DIRECT_CHAR)
			ft_check_dir(str, root, com, j);
		else if (com->arg[j] & T_IND)
			ft_check_ind(str, root, com, j);
		else
			ft_close_error(37);
		j++;
	}
}

static void	ft_size_byte_ins(t_root *root, t_op *com)
{
	t_com	*tmp_c;

	tmp_c = root->ins_end->data;
	tmp_c->o_size++;
	if (com->t_dec)
		tmp_c->o_size++;
	else
		tmp_c->t_dec = 0;
	tmp_c->a_size = root->all_byte;
	root->all_byte += tmp_c->o_size;
	tmp_c->line = root->line;
}

void		ft_add_command(char *str, t_root *root)
{
	int		i;
	int		j;

	j = 0;
	i = ft_check_name_command(str, g_com);
	if (i < 0)
		ft_close_error(47);
	str = str + g_com[i].n_sym;
	while (str && *str && (*str == 32 || *str == '\t'))
		str++;
	if (!str || !*str || *str == SEPARATOR_CHAR)
		ft_close_error(35);
	ft_check_argument(&str, g_com + i, root);

//	while (j < g_com[i].n_arg)
//	{
//		if (str && *str == SEPARATOR_CHAR)
//			str++;
//		while (str && *str && (*str == 32 || *str == '\t'))
//			str++;
//		if ((g_com[i].arg[j] & T_REG) && *str == REGISTOR_CHAR)
//			ft_check_registor(&str, g_com + i, tmp_com, j);
//		else if ((g_com[i].arg[j] & T_DIR) && *str == DIRECT_CHAR)
//			ft_check_dir(&str, g_com + i, tmp_com, j, root);
//		else if (g_com[i].arg[j] & T_IND)
//			ft_check_ind(&str, g_com + i, tmp_com, j, root);
//		else
//			ft_close_error(37);
//		j++;
//	}
	ft_size_byte_ins(root, g_com + i);

//	tmp_com->o_size++;
//	if (g_com[i].t_dec)
//		tmp_com->o_size++;
//	else
//		tmp_com->t_dec = 0;
//	tmp_com->a_size = root->all_byte;
//	root->all_byte += tmp_com->o_size;
//	tmp_com->line = root->line;

	if (str && *str)
		ft_close_error(39);
}
