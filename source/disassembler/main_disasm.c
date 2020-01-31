/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_disasm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:29:16 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:29:20 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_g_com.h"
#include "../../includes/dis_asm.h"

void			ft_init_data(t_data **data)
{
	if (!((*data) = ft_memalloc(sizeof(t_data))))
		ft_error(0, 8);
	if (!((*data)->buf = ft_memalloc(sizeof(MAX_BUFFER))))
		ft_error(0, 9);
}


char			*ft_create_file_name(char *av)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_strdup(av);
	if (!(tmp = ft_strrchr(tmp2, '.')))
		ft_error(0, 5);
	if (!tmp || ft_strcmp(tmp, FILE_EXT_IN))
		ft_error(0, 6);
	*tmp = '\0';
	tmp = tmp2;
	if (!(tmp2 = ft_strjoin(tmp2, FILE_EXT_OUT)))
		ft_error(0, 7);
	free(tmp);
	return (tmp2);
}

int				main(int ac, char **av)
{
	t_data		*data;

	if (ac == 1)
		ft_error(0, 0);
	ft_init_data(&data);
	data->file = ft_create_file_name(av[1]);
	ft_read_cor(data, av[1]);
	ft_dis_header(data);
	ft_dis_command(data);
	ft_putstr("Writing output program to ");
	ft_putendl(data->file);
	close(data->fd[0]);
	close(data->fd[1]);
	return (0);
}
