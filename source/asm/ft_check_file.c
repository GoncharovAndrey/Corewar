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

void			ft_save_str(char **name_comment, char *tmp, size_t size)
{
	if (!(*name_comment = ft_strnew(size)))
		ft_close_error(8);
	ft_strncpy(*name_comment, tmp, size);
}

void			ft_check_continue(char **name_comment, int fd, char *tmp_in)
{
	char		*tmp_read;
	char		*tmp;
	char		*tmp_copy;
	size_t		size;

	*name_comment = ft_strjoin(tmp_in, "\n");
	while (get_next_line(fd, &tmp_read) > 0)
	{
		tmp = ft_strchr(tmp_read, '"');
		if (!tmp)
		{
			tmp = *name_comment;
			*name_comment = ft_strjoin(*name_comment, tmp_read);
			free(tmp);
			free(tmp_read);
			tmp = *name_comment;
			*name_comment = ft_strjoin(*name_comment, "\n");
			free(tmp);
			continue;
		}
		else
		{
			size = (size_t)(tmp);
			size -= (size_t)tmp_read;
			tmp_copy = ft_strnew(size);
			ft_strncpy(tmp_copy, tmp_read, size);
			tmp++;
			while (tmp && *tmp && (*tmp == 32 || *tmp == '\t'))
				tmp++;
			if (tmp && *tmp && *tmp != COMMENT_CHAR && *tmp != ALT_COMMENT_CHAR)
				ft_close_error(9);
			free(tmp_read);
			tmp_read = *name_comment;
			*name_comment = ft_strjoin(*name_comment, tmp_copy);
			free(tmp_read);
			break ;
		}
	}
}

void			ft_check_name(int fd, char **name_comment)
{
	char		*tmp[8];
	int			name_com;
	int			hooks[2];

	hooks[0] = 0;
	hooks[1] = 0;
	ft_memset(tmp, 0, sizeof(char*) * 8);
	while (get_next_line(fd, tmp) > 0)
	{
		name_com = 0;
		tmp[1] = tmp[0];
		while (tmp[0] && (*tmp[0] == 32 || *tmp[0] == '\t'))
			tmp[0]++;
		if (!tmp[0] || !*tmp[0] || *tmp[0] == COMMENT_CHAR || *tmp[0] == ALT_COMMENT_CHAR)
		{
			free(tmp[1]);
			continue;
		}
		if (!tmp[0] || !*tmp[0] || *tmp[0] != NAME_CMD_STRING[0] || *tmp[0] != COMMENT_CMD_STRING[0])
			ft_close_error(3);
		if ((ft_strstr(tmp[0], NAME_CMD_STRING)) != tmp[0])
		{
			name_com = 1;
			if ((ft_strstr(tmp[0], COMMENT_CMD_STRING)) != tmp[0])
				ft_close_error(4);
		}
		tmp[0] += 1;
		while (tmp[0] && *tmp[0] && *tmp[0] != 32 && *tmp[0] != '\t' && *tmp[0] != '"')
			tmp[0]++;
		while (tmp[0] && *tmp[0] && (*tmp[0] == 32 || *tmp[0] == '\t'))
			tmp[0]++;
		if (!tmp[0] || !*tmp[0] || *tmp[0] != '"')
			ft_close_error(5);
		hooks[0] = 1;
		tmp[0]++;
		tmp[2] = tmp[0];
		while (tmp[0] && *tmp[0] && *tmp[0] != '"')
			tmp[0]++;
		if (!tmp[0] || !*tmp[0])
		{
			ft_check_continue(name_comment + name_com, fd, tmp[2]);
		}
		else
		{
			tmp[3] = tmp[0];
			tmp[0]++;
			while (tmp[0] && *tmp[0] && (*tmp[0] == 32 || *tmp[0] == '\t'))
				tmp[0]++;
			if (tmp[0] && *tmp[0] && (*tmp[0] != COMMENT_CHAR || *tmp[0] != ALT_COMMENT_CHAR))
				ft_close_error(6);
			ft_save_str(name_comment + name_com, tmp[2], tmp[3] - tmp[2]);
		}
		free(tmp[1]);
		if (name_comment[0] && ft_strlen(name_comment[0]) > PROG_NAME_LENGTH)
			ft_close_error(10);
		if (name_comment[1] && ft_strlen(name_comment[1]) > PROG_NAME_LENGTH)
			ft_close_error(11);
		if (name_comment[0] && name_comment[1])
			break;
	}
}