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
# include <limits.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "op.h"

# define REG_BYTE		1
# define COM_CHAR	'"'

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
	unsigned long int	arg[3];
	struct s_label		*ind[3];
	unsigned char		byte[3];
	unsigned char 		o_size;
	unsigned long int	a_size;
	size_t				line;
}						t_com;

typedef struct			s_label
{
	char				*str;
	unsigned long int	pos;
	int					status;
	size_t				line;
//	t_dlist				*head;
}						t_label;

typedef struct			s_root
{
	t_header			*header;
	t_dlist				*instruction;
	t_dlist				*ins_end;
	unsigned long int	all_byte;
	t_dlist				*label;
	char				*lbl_char;
	size_t				line;
}						t_root;

static t_op				g_com[17] =
{
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
			{0, 0, 0, 0, {0}, 0,0}
};

void					ft_close_error();
void					ft_check_name(int fd, t_root *root);
t_dlist					*ft_add_prev(t_dlist *node, t_dlist *tmp);
t_dlist					*ft_cut_dlist(t_dlist *del, t_dlist **head);
t_dlist					*ft_add_next(t_dlist *node, t_dlist *tmp);
t_dlist					*ft_creat_node(size_t size);
void					ft_check_command(int fd, t_root *root);
int						ft_check_label(char **str, t_root *root);
t_label					*ft_find_label(char *str, t_dlist *label);
void					ft_no_such_label(t_root *root);
void					ft_write_cor(t_root *root, int	fd);
unsigned int			ft_atoi_umax(char **str);
void					ft_add_command(char *str, t_root *root);
void					ft_check_registor(char **str, t_root *root, t_op *com, int j);
void					ft_check_ind(char **str, t_root *root, t_op *com, int j);
void					ft_check_dir(char **str, t_root *root, t_op *com, int j);


#endif

