/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:58:27 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:58:29 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dis_asm.h"

void		ft_error(int fd, int num)
{
	if (fd)
		close(fd);
	ft_putnbr_fd(num, 2);
	exit(EXIT_FAILURE);
}
