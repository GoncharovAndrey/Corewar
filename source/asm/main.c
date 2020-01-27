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
	t_root		root;
	char		*name;
	int			fd[2];
	char		*tmp[2];

	if (ac == 1)
		ft_close_error(0);
	root.header = (t_header*)ft_memalloc(sizeof(t_header));
	ft_memset(&root,0,sizeof(t_root));
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_close_error(1);
	root.lbl_char = ft_strjoin(LABEL_CHARS, NULL);
	name = ft_create_name(av[1]);
	if ((fd[1] = open(name,O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		ft_close_error(2);
	ft_memset(tmp, 0, sizeof(char*) * 2);




//	ft_check_name(fd[0], &root);

	ft_check_command(fd[0], &root);

//	ft_strcpy(root.header->prog_name, tmp[0]);
//	ft_strcpy(root.header->comment, tmp[1]);
	root.header->magic = COREWAR_EXEC_MAGIC;
	root.header->prog_size = (unsigned int)root.all_byte;
//	t_dlist *tmp_dl;

//	tmp = root.instruction;
//	while ();
	ft_no_such_label(&root);
	printf("%zu all_byte\n", root.all_byte);
	t_dlist	*tmp_dl;
	t_com	*tmp_com;
	tmp_dl = root.instruction;
	while (tmp_dl)
	{
		tmp_com = tmp_dl->data;
//		printf("{%hhu %hhu} {%lu %lu %lu} {%p %p %p} {%hhu %hhu %hhu} {%hhu %lu}\n", tmp_com->n_com, tmp_com->t_dec, tmp_com->arg[0], tmp_com->arg[1], tmp_com->arg[2], tmp_com->ind[0], tmp_com->ind[1], tmp_com->ind[2], tmp_com->byte[0], tmp_com->byte[1], tmp_com->byte[2], tmp_com->o_size, tmp_com->a_size);
		tmp_dl = tmp_dl->next;
	}
	ft_write_cor(&root, fd[1]);
//	printf("%lu\n", ((t_com*)(root.instruction->data))->a_size);
//	printf("{%s} str\n", ((t_label*)(root.label->data))->str);
//	printf("%p\n", name);
	close(fd[0]);
	close(fd[1]);
	free(name);
	exit(EXIT_SUCCESS);
//	free(root.commmand);
	return (0);
}