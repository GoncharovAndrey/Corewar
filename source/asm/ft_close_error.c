/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 09:56:43 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/29 09:56:45 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"
#include "../../includes/asm_error.h"

void			ft_close_error(char *str, t_root *root)
{
	ft_putstr_fd(str, 2);
	if (root && root->line)
	{
		ft_putnbr_fd(root->line, 2);
		ft_putstr("]\n");
	}
	if (root && root->fd[0])
		close(root->fd[0]);
	if (root)
		ft_del_root(&root);
	exit(EXIT_FAILURE);
}
