/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:27:17 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/23 11:27:19 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"

static void		ft_check_last_symbol(t_root *root, int fd)
{
	t_dlist		*tmp_dl;
	t_com		*tmp_com;
	char		tmp[1];

	tmp_dl = root->ins_end;
	if (tmp_dl->prev)
	{
		tmp_dl->prev->next = NULL;
		root->ins_end = tmp_dl->prev;
		free(tmp_dl->data);
		free(tmp_dl);
	}
	lseek(fd, -1, SEEK_CUR);
	read(fd, tmp, 1);
	if (*tmp != '\n')
	{
		tmp_com = root->ins_end->data;
		if (tmp_com->line == root->line)
			ft_close_error(187);
		if (root->label)
			if (((t_label*)(root->label->data))->line == root->line)
				ft_close_error(188);
	}
}

static int		ft_skip_charters(char **str, char **str_copy)
{
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (!*str || !**str)
	{
		ft_strdel(str_copy);
		return (0);
	}
	return (1);
}

static void		ft_change_comment_char(char *str)
{
	char		*tmp;

	if ((tmp = ft_strchr(str, COMMENT_CHAR)))
		*tmp = '\0';
	if ((tmp = ft_strchr(str, ALT_COMMENT_CHAR)))
		*tmp = '\0';
}

void			ft_check_command(int fd, t_root *root)
{
	char		*tmp[2];

	root->instruction = ft_add_next(NULL, ft_creat_node(sizeof(t_com)));
	root->ins_end = root->instruction;
	while (get_next_line(fd, tmp) > 0)
	{
		root->line++;
		tmp[1] = tmp[0];
		ft_change_comment_char(*tmp);
		if (!(ft_skip_charters(tmp, tmp + 1)))
			continue;
		ft_check_label(tmp, root);
		if (!(ft_skip_charters(tmp, tmp + 1)))
			continue;
		ft_add_command(tmp[0], root);
		root->ins_end = ft_add_next(root->ins_end,
				ft_creat_node(sizeof(t_com)));
		((t_com*)(root->ins_end->data))->a_size = root->all_byte;
		free(tmp[1]);
	}
	ft_check_last_symbol(root, fd);
}
