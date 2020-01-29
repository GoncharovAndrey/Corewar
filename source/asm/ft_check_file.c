/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:03:45 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/22 11:03:48 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"
#include "../../includes/asm_error.h"

static void		ft_available_name_com(t_root *root, char **tmp, int name_com)
{
	if (tmp)
		if (*(tmp + name_com))
			ft_close_error(DUPLICATE_ERR, root);
	root->line++;
	root->line--;
}

static char		*ft_cpy_name(t_root *root, int name_com, char *start, char *end)
{
	if (name_com == 4)
	{
		if ((end - start) <= PROG_NAME_LENGTH)
			return (ft_strncpy(root->header->prog_name, start, end - start));
		else
			ft_close_error(NAME_SIZE, NULL);
	}
	else if (name_com == 5)
	{
		if ((end - start) <= COMMENT_LENGTH)
			return (ft_strncpy(root->header->comment, start, end - start));
		else
			ft_close_error(NAME_SIZE, NULL);
	}
	return (NULL);
}

static int		ft_valid_name(char **str, t_root *root)
{
	char		*tmp;
	int			res;

	res = -1;
	tmp = *str;
	if (**str != NAME_CMD_STRING[0] || **str != COMMENT_CMD_STRING[0])
		ft_close_error(SYNTAX_ERROR, root);
	while (*str && **str && **str != 32 && **str != '\t' && **str != COM_CHAR)
		(*str)++;
	if (!*str || !**str)
		ft_close_error(SYNTAX_ERROR, root);
	if (**str != 32 && **str != '\t' && **str != COM_CHAR)
		ft_close_error(SYNTAX_ERROR, root);
	tmp = ft_strsub(tmp, 0, *str - tmp);
	if (!ft_strcmp(tmp, NAME_CMD_STRING))
		res = 4;
	else if (!ft_strcmp(tmp, COMMENT_CMD_STRING))
		res = 5;
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (!*str || !**str || **str != COM_CHAR)
		ft_close_error(SYNTAX_ERROR, root);
	(*str)++;
	free(tmp);
	return (res);
}

static int		ft_fu_norm(t_root *root, char **str, char **del)
{
	root->line++;
	*del = *str;
	return (ft_check_com_char(str, del));
}

void			ft_check_name(int fd, t_root *root)
{
	char		*tmp[6];
	int			name_com;

	ft_bzero(tmp, sizeof(char*) * 6);
	while (get_next_line(fd, tmp) > 0)
	{
		if (!ft_fu_norm(root, tmp, tmp + 1))
			continue ;
		if ((name_com = ft_valid_name(tmp, root)) == -1)
			ft_close_error(SYNTAX_ERROR, root);
		ft_available_name_com(root, tmp, name_com);
		if ((tmp[2] = ft_strchr(tmp[0], COM_CHAR)) == NULL)
			tmp[name_com] = ft_check_continue(root, fd, tmp[0], name_com);
		else
		{
			tmp[name_com] = ft_cpy_name(root, name_com, tmp[0], tmp[2]++);
			if (ft_check_com_char(tmp + 2, tmp + 1) == 1)
				ft_close_error(SYNTAX_ERROR, root);
		}
		ft_strdel(tmp + 1);
		if (tmp[4] && tmp[5])
			return ;
	}
	ft_close_error(DUPLICATE_ERR, root);
}
