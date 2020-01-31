/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:07:47 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:07:50 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"
#include "../../includes/asm_error.h"

int				main(int ac, char **av)
{
	t_root		*root;

	if (ac == 1)
		ft_close_error(OPEN_ERROR, NULL);
	ft_init_root(&root);
	root->name = ft_create_name(av[1], root);
	root->fd[0] = open(av[1], O_RDONLY);
	if (root->fd[0] == -1)
		ft_close_error(OPEN_ERROR, root);
	ft_check_name(root->fd[0], root);
	ft_check_command(root->fd[0], root);
	ft_no_such_label(root);
	if ((root->fd[1] = open(root->name, O_WRONLY | O_CREAT | O_TRUNC, 0666))
		== -1)
		ft_close_error(CREATE_F_ERROR, NULL);
	ft_write_cor(root, root->fd[1]);
	ft_putstr("Writing output program to ");
	ft_putendl(root->name);
	close(root->fd[0]);
	close(root->fd[1]);
	ft_del_root(&root);
	return (0);
}
