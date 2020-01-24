/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:18:33 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/23 13:18:34 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void				ft_print_byte(char *buf)
{
	int 			i;
	unsigned char	b;

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

int					main(int ac, char **av)
{
	int				fd;
	char			buf[4096];
	char			*tmp;
	int				rd;


	fd = open(av[1], O_RDONLY);
	printf("%d\n", fd);
	rd = read(fd, buf, 2192);
	printf("%d\n", rd);
//	ft_memset(buf, 0, 4096);
	rd = read(fd, buf, 4096);
	printf("%d\n", rd);
	tmp = buf;
	while (rd-- > 0)
	{
		ft_print_byte(tmp);
		write(1, " ", 1);
		tmp++;
	}
	char	*str;
	return (0);
}
