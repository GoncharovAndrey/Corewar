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

size_t			ft_cat_name_n(t_root *root, int name_com, char *start, char *end)
{
	size_t		len;

	len = 0;
	if (name_com == 4)
	{
		len = ft_strlen(root->header->prog_name);
		len = len + (end - start);
		if (len + 1 <= PROG_NAME_LENGTH)
			ft_strncat(root->header->prog_name, start, end - start);
		else
			ft_close_error(17);
	}
	else if (name_com == 5)
	{
		len = ft_strlen(root->header->comment);
		len = len + (end - start);
		if (len + 1 <= COMMENT_LENGTH)
			ft_strncat(root->header->comment, start, end  - start);
		else
			ft_close_error(17);
	}
	return (len);
}

void			ft_available_name_com(t_root *root, int name_com)
{
	if (name_com == 4)
	{
		if (root->header->prog_name[0])
			ft_close_error(564);
	}
	else if (name_com == 5)
	{
		if (root->header->comment[0])
			ft_close_error(564);
	}
}


char			*ft_check_continue(t_root *root, int fd, char *tmp_in, int name_com)
{
	size_t		size;
	char		*tmp_read;
	char		*tmp_end;

	ft_available_name_com(root, name_com);
	size = ft_strlen(tmp_in);
	size = ft_cat_name_n(root, name_com, tmp_in, tmp_in + size);
	if (name_com == 4)
		root->header->prog_name[size] = '\n';
	else if (name_com == 5)
		root->header->comment[size] = '\n';
	while (get_next_line(fd, &tmp_read) > 0)
	{
		root->line++;
		tmp_end = ft_strchr(tmp_read, COM_CHAR);
		if (!tmp_end)
		{
			size = ft_strlen(tmp_read);
			size = ft_cat_name_n(root, name_com, tmp_read, tmp_read + size);
			if (name_com == 4)
				root->header->prog_name[size] = '\n';
			else if (name_com == 5)
				root->header->comment[size] = '\n';
			free(tmp_read);
			continue;
		}
		else
		{
			size = ft_cat_name_n(root, name_com, tmp_read, tmp_end);
			tmp_end++;
			if (ft_check_com_char(tmp_end, tmp_read) == 1)
				ft_close_error(455);
			free(tmp_read);
			break ;
		}
	}
	if (name_com == 4)
		return (root->header->prog_name);
	else if (name_com == 5)
		return (root->header->comment);
	return (NULL);
}

char			*ft_cpy_name(t_root *root, int name_com, char *start, char *end)
{
	if (name_com == 4)
	{
		if ((end - start) <= PROG_NAME_LENGTH)
			return (ft_strncpy(root->header->prog_name, start, end - start));
		else
			ft_close_error(17);
	}
	else if (name_com == 5)
	{
		if ((end - start) <= COMMENT_LENGTH)
			return (ft_strncpy(root->header->comment, start, end  - start));
		else
			ft_close_error(17);
	}
	return (NULL);
}

int				ft_valid_name(char **str)
{
	char		*tmp;
	int			res;

	res = -1;
	tmp = *str;
	if (!*str || !**str || **str != NAME_CMD_STRING[0] || **str != COMMENT_CMD_STRING[0])
		ft_close_error(39);
	while (*str && **str && **str != 32 && **str != '\t' && **str != COM_CHAR)
		(*str)++;
	if (!*str || !**str)
		ft_close_error(144);
	if (**str != 32 && **str != '\t' && **str != COM_CHAR)
		ft_close_error(155);
	tmp = ft_strsub(tmp, 0, *str - tmp);
	if (!ft_strcmp(tmp, NAME_CMD_STRING))
		res = 4;
	else if (!ft_strcmp(tmp, COMMENT_CMD_STRING))
		res = 5;
	while (*str && **str && **str != COM_CHAR)
		(*str)++;
	if (!*str || !**str)
		ft_close_error(166);
	(*str)++;
	free(tmp);
	return (res);
}

int				ft_check_com_char(char **str, char **del)
{
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (!*str || !**str || **str == COMMENT_CHAR || **str == ALT_COMMENT_CHAR)
	{
		ft_strdel(del);
		return (0);
	}
	return (1);
}

void			ft_check_name(int fd, t_root *root)
{
	char		*tmp[6];
	int			name_com;

	ft_bzero(tmp,sizeof(char*) * 6);
	while (get_next_line(fd, tmp) > 0)
	{
		root->line++;
		tmp[1] = tmp[0];
		if (!ft_check_com_char(tmp, tmp + 1))
			continue;
		if ((name_com = ft_valid_name(tmp)) == -1)
			ft_close_error(878);
		if ((tmp[2] = ft_strchr(tmp[0], COM_CHAR)) == NULL)
			tmp[name_com] = ft_check_continue(root, fd, tmp[0], name_com);
		else
		{
			ft_available_name_com(root, name_com);
			tmp[name_com] = ft_cpy_name(root, name_com, tmp[0], ++tmp[2]);
			if (ft_check_com_char(tmp + 2, tmp + 1) == 1)
				ft_close_error(455);
		}
		ft_strdel(tmp + 1);
		if (tmp[4] && tmp[5])
			break;
	}
}
