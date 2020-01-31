/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_asm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:32:54 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:32:56 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIS_ASM_H
# define DIS_ASM_H

# include <limits.h>
# include "op.h"
#include "../lib/libft/libft.h"
# define MAX_BUFFER		4096
# define FILE_EXT_IN	".cor"
# define FILE_EXT_OUT	".s"

typedef struct			s_data
{
	char				*file;
	char				*buf;
	unsigned char		*name;
	unsigned char		*command;
	int					fd[2];
	size_t				lenght;
}						t_data;

typedef struct			s_dcom
{
	int					name;
	unsigned char		type[4];
}						t_dcom;


void					ft_error(int fd, int num);
void					ft_read_cor(t_data *data, char *str);
void					ft_dis_header(t_data *data);
void					ft_dis_command(t_data *data);
unsigned int			ft_read_number(unsigned char *str, unsigned short int byte);

#endif