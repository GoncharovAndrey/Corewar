/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:04:03 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/23 19:04:05 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_op		*ft_init_command(void)
{
	t_op	*tmp;

	if (!(tmp = (t_op*)malloc(sizeof(t_op) * 17)))
		ft_close_error(11);
	ft_memset(tmp, 0, sizeof(t_op) * 17);
	t_op	tmp_2[16] = {
			{1, "live", 4, 1, {T_DIR}, 0, 4},
			{2, "ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 4},
			{3, "st", 2, 2, {T_REG, T_IND | T_REG}, 1, 4},
			{4, "add", 3, 3, {T_REG, T_REG, T_REG}, 1, 4},
			{5, "sub", 3, 3, {T_REG, T_REG, T_REG}, 1, 4},
			{6, "and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
			{7, "or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
			{8, "xor", 3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
			{9, "zjmp", 4, 1, {T_DIR}, 0, 2},
			{10, "ldi", 3,3,  {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
			{11, "sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
			{12, "fork", 4, 1, {T_DIR}, 0, 2},
			{13, "lld", 3, 2, {T_DIR | T_IND, T_REG}, 1, 4},
			{14, "lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
			{15, "lfork", 5, 1, {T_DIR}, 0, 2},
			{16, "aff", 3, 1, {T_REG}, 1, 2},
			};

	return (ft_memcpy(tmp, tmp_2, sizeof(t_op) * 16));
}
