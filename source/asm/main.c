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
#include "../../includes/asm_g_com.h"

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

void			ft_init_root(t_root **root)
{
	if (!((*root) = ft_memalloc(sizeof(t_root))))
		ft_close_error(79);
	if (!((*root)->header = ft_memalloc(sizeof(t_header))))
		ft_close_error(79);
	if (!((*root)->lbl_char = ft_strjoin(LABEL_CHARS, NULL)))
		ft_close_error(79);
	(*root)->line = 0;
	(*root)->header->magic = COREWAR_EXEC_MAGIC;

}

int				main(int ac, char **av)
{
	t_root		*root;
	char		*name;
	int			fd[2];

	if (ac == 1)
		ft_close_error(0);
	ft_init_root(&root);
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_close_error(1);
	name = ft_create_name(av[1]);
	ft_check_name(fd[0], root);
	ft_check_command(fd[0], root);
	ft_no_such_label(root);
	if ((fd[1] = open(name,O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		ft_close_error(2);
	ft_write_cor(root, fd[1]);
	ft_putstr("Writing output program to ");
	ft_putendl(name);
	close(fd[0]);
	close(fd[1]);
	free(name);
	exit(EXIT_SUCCESS);
	return (0);
}