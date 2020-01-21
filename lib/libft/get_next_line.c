/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:28:30 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/24 14:21:41 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_strncut(char **dst, size_t i, int fd)
{
	size_t			len;
	char			*tmp;

	len = ft_strlen(dst[fd]);
	tmp = ft_strsub(dst[fd], i + 1, len - i);
	ft_strdel(&dst[fd]);
	dst[fd] = tmp;
}

static char			*ft_pr_strjoin(char **dst, char *src, int fd)
{
	char			*tmp;

	if (!(tmp = ft_strjoin(dst[fd], src)))
		return (NULL);
	ft_strdel(&dst[fd]);
	dst[fd] = tmp;
	return (dst[fd]);
}

static int			ft_read(char **dst, const int fd)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(ft_pr_strjoin(dst, buf, fd)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	return (ret > 0);
}

static int			ft_writing(char **dst, char **line, int fd, int ret)
{
	size_t			i;

	i = 0;
	while (dst[fd][i] && dst[fd][i] != '\n')
		i++;
	if (ret == 0 && (dst[fd] == NULL || dst[fd][0] == '\0'))
	{
		*line = NULL;
		ft_strdel(&dst[fd]);
		return (0);
	}
	if (!(*line = ft_strsub(dst[fd], 0, i)))
	{
		ft_strdel(&dst[fd]);
		return (-1);
	}
	ft_strncut(dst, i, fd);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static	char	*fd_buf[4096];
	int				ret;

	if (!line)
		return (-1);
	ret = BUFF_SIZE;
	if (fd < 0 || fd > 4096 || ret > 65534)
	{
		*line = NULL;
		return (-1);
	}
	if (!fd_buf[fd])
		if (!(fd_buf[fd] = ft_strnew(0)))
			return (-1);
	if (ft_strchr(fd_buf[fd], '\n'))
		return (ft_writing(fd_buf, line, fd, 0));
	if ((ret = ft_read(fd_buf, fd)) < 0)
	{
		ft_strdel(&fd_buf[fd]);
		*line = NULL;
		return (-1);
	}
	return (ft_writing(fd_buf, line, fd, ret));
}
