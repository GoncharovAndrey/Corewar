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

void			ft_close_error(int error)
{
	printf("%d error\n", error);
	ft_putendl_fd("ERROR", 2);
	exit(EXIT_FAILURE);
}
