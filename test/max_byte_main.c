/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_byte_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:16:42 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/25 13:16:44 by cjosue           ###   ########.fr       */
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
	char			*tmp;
	char			buf[1];
	int 			fd;
	int				i;

	fd = open(av[1] , O_RDONLY);
	while((i = get_next_line(fd, &tmp)) > 0)
	{
		printf("%d\n", i);
		free(tmp);
		lseek(fd, -1, SEEK_CUR);
		read(fd, buf, 1);
//		if (*buf != '\n')
			printf("{%c}\n", *buf);
	}

//	unsigned char	*res;
//	char			*str = "0abf11a0";
//	char			*tmp;
//	int				byte;
//
//	byte = 4;
//	res = (unsigned char*)malloc(sizeof(unsigned char) * byte);
//	tmp = str;
//	while (*tmp)
//	{
//		*res = 0;
//		if (*tmp >= '0' && *tmp  <='9')
//			*res |= ((*tmp - '0') << 4);
//		else
//			*res |= ((*tmp - 'a' + 10) << 4);
//		tmp++;
//		if (*tmp >= '0' && *tmp  <='9')
//			*res |= *tmp - '0';
//		else
//			*res |= *tmp - 'a' + 10;
//		tmp++;
//		res++;
//
//	}
//	int fd;
//	fd = open(av[1], O_WRONLY);
//	write(fd, res - byte, byte);
//	int		i;
//	unsigned int tmp;

//	i = 19;
//	tmp = (unsigned int)i;
//	ft_print_byte((char*)&tmp);
	return (0);
}