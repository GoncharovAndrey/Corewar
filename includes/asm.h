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
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "op.h"
# define REG_BYTE		1
# define COM_CHAR		'"'

typedef struct			s_dlist
{
	void				*data;
	struct s_dlist		*next;
	struct s_dlist		*prev;
}						t_dlist;

typedef struct			s_op
{
	unsigned char		n_com;
	char				*name;
	int					n_sym;
	int					n_arg;
	int					arg[4];
	int					t_dec;
	int					s_dir;
}						t_op;

typedef struct			s_com
{
	unsigned char		n_com;
	unsigned char		t_dec;
	unsigned long int	arg[3];
	struct s_label		*ind[3];
	unsigned char		byte[3];
	unsigned char		o_size;
	unsigned long int	a_size;
	size_t				line;
}						t_com;

typedef struct			s_label
{
	char				*str;
	unsigned long int	pos;
	int					status;
	size_t				line;
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

void					ft_close_error();
void					ft_check_name(int fd, t_root *root);
t_dlist					*ft_add_next(t_dlist *node, t_dlist *tmp);
t_dlist					*ft_creat_node(size_t size);
void					ft_check_command(int fd, t_root *root);
int						ft_check_label(char **str, t_root *root);
t_label					*ft_find_label(char *str, t_dlist *label);
void					ft_no_such_label(t_root *root);
void					ft_write_cor(t_root *root, int	fd);
unsigned int			ft_atoi_umax(char **str);
void					ft_add_command(char *str, t_root *root);
void					ft_check_reg(char **str, t_root *root,
						t_op *com, int j);
void					ft_check_ind(char **str, t_root *root,
						t_op *com, int j);
void					ft_check_dir(char **str, t_root *root,
						t_op *com, int j);
char					*ft_check_continue(t_root *root, int fd,
						char *tmp_in, int name_com);
int						ft_check_com_char(char **str, char **del);

#endif
