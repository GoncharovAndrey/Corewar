/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:35:05 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/21 17:35:11 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <fcntl.h>
#include "../../includes/asm.h"

void			ft_close_error()
{
	ft_putendl_fd("ERROR", 2);
	exit(EXIT_FAILURE);
}

char			*ft_create_name(char *av)
{
	char		*tmp;
	char		*tmp2;

	tmp = NULL;
	tmp2 = av;
	while ((tmp2 = ft_strchr(tmp2, '.')) != NULL)
	{
		tmp2++;
		tmp = tmp2;
	}
	if (!tmp || *tmp != 's' || *(tmp + 1))
		ft_close_error();
	tmp -= 1;
	*tmp = '\0';
	return (ft_strjoin(av, ".cor"));
}

int				main(int ac, char **av)
{
	char		*name;
	int			fd[2];

	if (ac == 1)
		ft_close_error();
	if ((fd[0] = open(av[1], O_RDONLY) == -1))
		ft_close_error();
	name = ft_create_name(av[1]);
	if ((fd[1] = open(name,O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		ft_close_error();
	printf("%s\n", name);
	int			ha;

	ha = 0x21204148;
	write(fd[1], &ha, 4);
	close(fd[0]);
	close(fd[1]);
	free(name);
	return (0);
}