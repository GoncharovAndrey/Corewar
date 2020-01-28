/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_g_com.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:59:03 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/28 19:59:05 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_G_COM_H
# define ASM_G_COM_H
# include "asm.h"
# include "op.h"

static t_op	g_com[17] =
{
	{1, "live", 4, 1, {T_DIR}, 0, 4},
	{2, "ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{3, "st", 2, 2, {T_REG, T_IND | T_REG}, 1, 4},
	{4, "add", 3, 3, {T_REG, T_REG, T_REG}, 1, 4},
	{5, "sub", 3, 3, {T_REG, T_REG, T_REG}, 1, 4},
	{6, "and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		1, 4},
	{7, "or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		1, 4},
	{8, "xor", 3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		1, 4},
	{9, "zjmp", 4, 1, {T_DIR}, 0, 2},
	{10, "ldi", 3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{11, "sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
	{12, "fork", 4, 1, {T_DIR}, 0, 2},
	{13, "lld", 3, 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{14, "lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{15, "lfork", 5, 1, {T_DIR}, 0, 2},
	{16, "aff", 3, 1, {T_REG}, 1, 2},
	{0, 0, 0, 0, {0}, 0, 0}
};

#endif
