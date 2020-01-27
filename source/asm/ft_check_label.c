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

void			ft_no_such_label(t_root *root)
{
	t_dlist		*tmp;
	t_label		*tmp_l;

	tmp = root->label;
	while (tmp)
	{
		tmp_l = tmp->data;
//		printf("%lu  {%s}\n", tmp_l->pos, tmp_l->str);
		if (tmp_l->status == 0)
			ft_close_error(199);
		tmp = tmp->prev;
	}
}

char		*ft_check_char(char *str, char *check)
{
	char	*tmp;
	char	*res;

	res = str;
//	printf
	while (str && *str != LABEL_CHAR)
	{
		if (*str == 32 || *str == '\t' || *str == DIRECT_CHAR || *str == SEPARATOR_CHAR || *str == '-')
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
		ft_close_error(41);
	return (res);
}

t_label		*ft_find_label(char *str, t_dlist *label)
{
	t_dlist	*tmp;
	t_label	*tmp_l;

	tmp = label;
//	printf("!!!!!!!!  %s  !!!!!!@\n", str);
	while (tmp)
	{
		tmp_l = (t_label*)tmp->data;
//		printf("{%s} \n", tmp_l->str);
		if (ft_strcmp(tmp_l->str, str) == 0)
		{
//			printf("FIND\n");
			return (tmp_l);
		}
		tmp = tmp->prev;
	}
//	printf("!!!!!!!!!\n");
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
		root->label = ft_add_next(root->label, ft_creat_node(sizeof(t_label)));
		tmp_l = (t_label*)root->label->data;
		tmp_l->status = 1;
		tmp_l->pos = root->all_byte;
		tmp_l->str = tmp2;
		tmp_l->line = root->line;
//		printf("%s   add label 1\n", tmp_l->str);
		return (1);
	}
	else if (tmp_l->status == 0)
	{
		tmp_l->pos = root->all_byte;
		tmp_l->status = 1;
	}
	free(tmp2);
	return (1);
}
