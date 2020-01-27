/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_rdi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:25:09 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/27 15:25:11 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char					*ft_check_char_ind(char **str, char *check)
{
	char				*tmp;
	char				*res;

	res = *str;
	while (*str && **str && **str != SEPARATOR_CHAR)
	{
		if (**str == 32 || **str == '\t')
		{
			res = ft_strsub(res, 0, *str - res);
			return (res);
		}
		tmp = check;
		while (tmp && *tmp)
		{
			if (**str == *tmp)
				break;
			tmp++;
		}
		if (!*tmp)
			ft_close_error(75);
		(*str)++;
	}
	res = ft_strsub(res, 0, *str - res);
	return (res);
}

void					ft_check_ind_lbl(char **str, t_root *root, int j)
{
	t_label				*tmp_l;
	char				*tmp_n;
	t_com				*ins;

	(*str)++;
	ins = root->ins_end->data;
	if (!(tmp_n = ft_check_char_ind(str, root->lbl_char)))
		ft_close_error(64);
	if (!(tmp_l = ft_find_label(tmp_n, root->label)))
	{
		root->label = ft_add_next(root->label, ft_creat_node(sizeof(t_label)));
		tmp_l = (t_label*)root->label->data;
		tmp_l->status = 0;
		tmp_l->str = tmp_n;
		ins->ind[j] = tmp_l;
	}
	else
	{
		ins->ind[j] = tmp_l;
		free(tmp_n);
	}
}

void					ft_check_dir(char **str, t_root *root, t_op *com, int j)
{
	t_com				*ins;

	ins = root->ins_end->data;
	(*str)++;
	if (**str == LABEL_CHAR)
		ft_check_ind_lbl(str, root, j);
	else if (**str == '-' || (**str >= '0' && **str <= '9'))
	{
		ins->arg[j] = (unsigned int)ft_atoi_umax(str);
		while (*str && **str && **str >= '0' && **str <= '9')
			(*str)++;
	}
	else
		ft_close_error(99);
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(45);
	ins->n_com = com->n_com;
	ins->byte[j] = com->s_dir;
	ins->t_dec |= (DIR_CODE << (6 - j * 2));
	ins->o_size += com->s_dir;
}

void					ft_check_ind(char **str, t_root *root, t_op *com, int j)
{
	t_com				*ins;

	ins = root->ins_end->data;
	if (**str == LABEL_CHAR)
		ft_check_ind_lbl(str, root, j);
	else if (**str == '-' || (**str >= '0' && **str <= '9'))
	{
		ins->arg[j] = (unsigned int)ft_atoi_umax(str);
		while (*str && **str && **str >= '0' && **str <= '9')
			(*str)++;
	}
	else
		ft_close_error(88);
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(46);
	ins->n_com = com->n_com;
	ins->byte[j] = IND_SIZE;
	ins->t_dec |= (IND_CODE << (6 - j * 2));
	ins->o_size += IND_SIZE;
}

void					ft_check_registor(char **str, t_root *root, t_op *com, int j)
{
	int					i;
	t_com				*ins;

	ins = root->ins_end->data;
	(*str)++;
	i = ft_atoi(*str);
	if (i > 99 || i < 0)
		ft_close_error(33);
	if (**str == '-')
		(*str)++;
	while (*str && **str && **str >= '0' && **str <= '9')
		(*str)++;
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(42);
	ins->n_com = com->n_com;
	ins->arg[j] = i;
	ins->t_dec |= (REG_CODE << (6 - j * 2));
	ins->byte[j] = REG_BYTE;
	ins->o_size += REG_BYTE;
}
