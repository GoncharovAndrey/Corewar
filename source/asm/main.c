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

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"

int				main(int ac, char **av)
{
	t_root		*root;
	char		*name;
	int			fd[2];

	if (ac == 1)
		ft_close_error(0);
	ft_init_root(&root);
	name = ft_create_name(av[1]);
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_close_error(1);
	ft_check_name(fd[0], root);
	ft_check_command(fd[0], root);
	ft_no_such_label(root);
	if ((fd[1] = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		ft_close_error(2);
	ft_write_cor(root, fd[1]);
	ft_putstr("Writing output program to ");
	ft_putendl(name);
	close(fd[0]);
	close(fd[1]);
	free(name);
	exit(EXIT_SUCCESS);
	return (0);
}
