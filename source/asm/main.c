/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:35:05 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/21 17:35:11 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_close_error(int error)
{
	printf("%d error\n", error);
	ft_putendl_fd("ERROR", 2);
	exit(EXIT_FAILURE);
}

void				ft_print_byte(char *buf)
{
	int 			i;

	i = 7;
	while (i >= 0)
	{
		if (*buf & (1U << i))
			ft_putchar('1');
		else
			ft_putchar('0');
		i--;
	}
}

unsigned short		*ft_reverse_order(short int g)
{
	unsigned short	*tmp;

	tmp = (unsigned short*)malloc(sizeof(unsigned short));
	*tmp = (unsigned short int)g;
	ft_print_byte((char*)tmp);
	printf("\n");
//	*tmp = ~*tmp;
	*tmp += 1;
	return (tmp);
}

char			*ft_create_name(char *av)
{
	char		*tmp;

	tmp = ft_strrchr(av, '.');
	tmp++;
	if (!tmp || *tmp != 's' || *(tmp + 1))
		ft_close_error(7);
	tmp--;
	*tmp = '\0';
	return (ft_strjoin(av, ".cor"));
}

int				main(int ac, char **av)
{
	char		*name;
	int			fd[2];
	char		*tmp[2];
	t_op		*topa;

	if (ac == 1)
		ft_close_error(0);
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_close_error(1);
	name = ft_create_name(av[1]);
	if ((fd[1] = open(name,O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		ft_close_error(2);
	ft_check_name(fd[0], tmp);
	write(fd[1], "{name}\n{", 8);
	while (tmp[0] && *tmp[0])
	{
		write(fd[1], tmp[0], 1);
		tmp[0]++;
	}
	write(fd[1], "}\n{comment}\n{", 13);
	while (tmp[1] && *tmp[1])
	{
		write(fd[1], tmp[1], 1);
		tmp[1]++;
	}
	write(fd[1], "}", 1);

	topa = ft_init_command();
	close(fd[0]);
	close(fd[1]);
	free(name);
	free(topa);
	return (0);
}