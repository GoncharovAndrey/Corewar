/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:38:31 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/25 15:38:34 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char		*ft_check_char(char *str, char *check)
{
	char	*tmp;
	char	*res;

	res = str;
	while (str && *str != LABEL_CHAR)
	{
		if (*str == 32 || *str == '\t')
			return (NULL);
		tmp = check;
		while (tmp && *tmp)
		{
			if (*str == *tmp)
				break;
			tmp++;
		}
		if (!*tmp)
			ft_close_error(75);
		str++;
	}
	if (!(res = ft_strsub(res, 0, str - res)))
		ft_close_error(44);
	return (res);
}

t_label		*ft_find_label(char *str, t_dlist *label)
{
	t_dlist	*tmp;
	t_label	*tmp_l;

	tmp = label;
	while (tmp)
	{
		tmp_l = (t_label*)label->data;
		if (ft_strcmp(tmp_l->str, str) == 0)
			return (tmp_l);
		tmp = tmp->next;
	}
	return (NULL);
}

int			ft_check_label(char **str, t_root *root)
{
	t_label	*tmp_l;
	char	*tmp;
	char	*tmp2;

	if (!(tmp = ft_strchr(*str, LABEL_CHAR)))
		return (0);
	if (!(tmp2 = ft_check_char(*str, root->lbl_char)))
		return (0);
	*str = tmp + 1;
	if (!(tmp_l = ft_find_label(tmp2, root->label)))
	{
		root->label = ft_add_prev(root->label, ft_creat_node(sizeof(t_label)));
		tmp_l = (t_label*)root->label->data;
		tmp_l->status = 1;
		tmp_l->pos = root->all_byte;
		tmp_l->str = tmp2;
		return (1);
	}
	else if (tmp_l->status == 0)
		tmp_l->status = 1;
	free(tmp2);
	return (1);
}

//void			ft_put_values(t_dlist *head, unsigned long int size)
//{
//	t_dlist		*tmp;
//	t_com		*tmp_c;
//
//	tmp = head;
//	while (tmp)
//	{
//		tmp_c = (t_com*)tmp->data;
//		if (tmp_c->arg[3] & 1)
//			tmp_c->arg[0] = size - tmp_c->a_size;
//		if (tmp_c->arg[3] & 2)
//			tmp_c->arg[1] = size - tmp_c->a_size;
//		if (tmp_c->arg[3] & 4)
//			tmp_c->arg[2] = size - tmp_c->a_size;
//		tmp = tmp->next;
//	}
//}