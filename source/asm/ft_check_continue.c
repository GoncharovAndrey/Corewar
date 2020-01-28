/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_continue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:31:27 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/28 18:31:29 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"

size_t			ft_cat_name_n(t_root *root, int nm_cm, char *strt, size_t size)
{
	size_t		len;

	len = 0;
	if (nm_cm == 4)
	{
		len = ft_strlen(root->header->prog_name);
		len = len + size;
		if (len + 1 <= PROG_NAME_LENGTH)
			ft_strncat(root->header->prog_name, strt, size);
		else
			ft_close_error(17);
	}
	else if (nm_cm == 5)
	{
		len = ft_strlen(root->header->comment);
		len = len + size;
		if (len + 1 <= COMMENT_LENGTH)
			ft_strncat(root->header->comment, strt, size);
		else
			ft_close_error(17);
	}
	return (len);
}

void			ft_for_cat(t_root *root, int name_com, char *str)
{
	size_t		size;

	size = ft_strlen(str);
	size = ft_cat_name_n(root, name_com, str, size);
	if (name_com == 4)
		root->header->prog_name[size] = '\n';
	else if (name_com == 5)
		root->header->comment[size] = '\n';
}

char			*ft_check_continue(t_root *root, int fd, char *in, int name_com)
{
	char		*tmp_read;
	char		*tmp_end;

	ft_for_cat(root, name_com, in);
	while (get_next_line(fd, &tmp_read) > 0)
	{
		root->line++;
		tmp_end = ft_strchr(tmp_read, COM_CHAR);
		if (!tmp_end)
		{
			ft_for_cat(root, name_com, tmp_read);
			free(tmp_read);
			continue;
		}
		else
		{
			ft_cat_name_n(root, name_com, tmp_read, (tmp_end++) - tmp_read);
			if (ft_check_com_char(&tmp_end, &tmp_read) == 1)
				ft_close_error(455);
			free(tmp_read);
			break ;
		}
	}
	return (root->header->prog_name);
}
