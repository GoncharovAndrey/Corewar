/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:35:45 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/21 17:35:47 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include <stdio.h>

#include <fcntl.h>
# include "../lib/libft/libft.h"
# include "op.h"

//typedef struct		s_command
//{
//	unsigned char	com;
//	unsigned char
//};
typedef struct			s_op
{
	unsigned char		n_com; /* number of command */
	char				*name; /*name command */
	int					n_sym; /*number symbol in name command */
	int					n_arg; /*number arguments */
	int					arg[3]; /*type arguments */
	int					t_dec; /*argument type declaration*/
	int					s_dir; /*size dir*/
}						t_op;

void					ft_close_error();
void					ft_check_name(int fd, char **name_comment);
t_op					*ft_init_command(void);

#endif
