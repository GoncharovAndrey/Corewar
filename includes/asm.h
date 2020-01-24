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

typedef struct			s_dlist
{
	void				*data;
	struct s_dlist		*next;
	struct s_dlist		*prev;
}						t_dlist;

typedef struct			s_op
{
	unsigned char		n_com; /* number of command */
	char				*name; /*name command */
	int					n_sym; /*number symbol in name command */
	int					n_arg; /*number arguments */
	int					arg[4]; /*type arguments */
	int					t_dec; /*argument type declaration*/
	int					s_dir; /*size dir*/
}						t_op;

typedef struct			s_com
{
	unsigned char		n_com;
	unsigned char		t_dec;
	unsigned int		arg[4];
	unsigned short		o_size;
	unsigned long int	a_size;
}						t_com;

typedef struct			s_label
{
	char				*str;
	unsigned long int	pos;
	int					status;
	t_dlist				*head;
}						t_label;

typedef struct			s_root
{
	t_op				*commmand;
	t_header			header;
	t_dlist				*instruction;
//	t_dlist				*unknow_label;
	t_dlist				*label;
	char				*lbl_char;
}						t_root;

void					ft_close_error();
void					ft_check_name(int fd, char **name_comment);
t_op					*ft_init_command(void);
t_dlist					*ft_add_prev(t_dlist *node, t_dlist *tmp);
t_dlist					*ft_cut_dlist(t_dlist *del, t_dlist **head);
t_dlist					*ft_add_next(t_dlist *node, t_dlist *tmp);
t_dlist					*ft_creat_node(size_t size);
void					ft_check_command(int fd, t_root *root);

#endif
