/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:27:17 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/23 11:27:19 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_check_last_symbol(t_root *root, int fd)
{
	t_dlist		*tmp_dl;
	t_com		*tmp_com;
	char		tmp[1];

	tmp_dl = root->ins_end;
	printf("%p\n", tmp_dl->prev);
	if (tmp_dl->prev)
	{
		tmp_dl->prev->next = NULL;
		root->ins_end = tmp_dl->prev;
		printf("tut\n");
		free(tmp_dl->data);
		free(tmp_dl);
	}
	lseek(fd, -1, SEEK_CUR);
	read(fd, tmp, 1);
	if (*tmp != '\n')
	{
		tmp_com = root->ins_end->data;
		if (tmp_com->line == root->line)
			ft_close_error(187);
		if (root->label)
			if (((t_label*)(root->label->data))->line == root->line)
				ft_close_error(188);
	}
}

int			ft_check_name_command(char *str, t_op *com)
{
	int		i;
	int		res;

	i = 0;
	res = -1;
	while (com[i].n_com)
	{
		if (ft_strncmp(str, com[i].name, com[i].n_sym) == 0)
			res = i;
		i++;
	}
	return (res);
}

void		ft_check_registor(char **str, t_op *com, t_com *ins, int j)
{
	int		i;

	(*str)++;
	i = ft_atoi(*str);
	if (i > 99 || i < 0)
		ft_close_error(33);
	if (**str == '-')
		(*str)++;
	while (*str && **str && **str >= '0' && **str <= '9')
		(*str)++;
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(42);
	ins->n_com = com->n_com;
	ins->arg[j] = i;
	ins->t_dec |= (REG_CODE << (6 - j * 2));
	ins->byte[j] = REG_BYTE;
	ins->o_size += REG_BYTE;
}

char		*ft_check_char_ind(char **str, char *check)
{
	char	*tmp;
	char	*res;

	printf("%s  - check label\n", *str);
	res = *str;
	while (*str && **str && **str != SEPARATOR_CHAR)
	{
		if (**str == 32 || **str == '\t')
		{
			if (!(res = ft_strsub(res, 0, *str - res)))
				ft_close_error(43);
			return (res);
		}
		tmp = check;
		while (tmp && *tmp)
		{
			if (**str == *tmp)
				break;
			tmp++;
		}
		if (!*tmp)
			ft_close_error(75);
		(*str)++;
	}
	if (!(res = ft_strsub(res, 0, *str - res)))
		ft_close_error(44);
	return (res);
}

void		ft_check_dir(char **str, t_op *com, t_com *ins, int j, t_root *root)
{
	(*str)++;
//	printf("%s  str\n", *str);
	unsigned long int	i;
	t_label				*tmp_l;

	i = 0;
	if (**str == LABEL_CHAR)
	{
		(*str)++;
		char			*tmp2;

		printf("{%s}  str\n", *str);
		tmp2 = ft_check_char_ind(str, root->lbl_char);
		if ((tmp_l = ft_find_label(tmp2, root->label)) == NULL)
		{
//			printf("{%s} str label!!!!!!!!!!!!!!!!\n", tmp2);
			root->label = ft_add_next(root->label, ft_creat_node(sizeof(t_label)));
			tmp_l = (t_label*)root->label->data;
			tmp_l->status = 0;
			tmp_l->pos = root->all_byte;
			tmp_l->str = tmp2;
			ins->ind[j] = tmp_l;
//			printf("%s   add label 0\n", tmp_l->str);
		}
		else
		{
			ins->ind[j] = tmp_l;
			free(tmp2);
		}
	}
	else if (**str == '-' || (**str >= '0' && **str <= '9'))
	{
		i = ft_atoi_umax(str);
//		if (**str == '-')
//			(*str)++;
		while (*str && **str && **str >= '0' && **str <= '9')
			(*str)++;
//		printf("%s\n", *str);
	}
	else
		ft_close_error(99);
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(45);
	ins->n_com = com->n_com;
	ins->arg[j] = (unsigned int)i;
	ins->byte[j] = com->s_dir;
	ins->t_dec |= (DIR_CODE << (6 - j * 2));
	ins->o_size += com->s_dir;
}

void		ft_check_ind(char **str, t_op *com, t_com *ins, int j, t_root *root)
{
	unsigned long int	i;
	t_label				*tmp_l;

	i = 0;
	if (**str == LABEL_CHAR)
	{
		(*str)++;
		char			*tmp2;

		tmp2 = ft_check_char_ind(str, root->lbl_char);
		if (!(tmp_l = ft_find_label(tmp2, root->label)))
		{
//			printf("%s str label\n", tmp2);
			root->label = ft_add_next(root->label, ft_creat_node(sizeof(t_label)));
			tmp_l = (t_label*)root->label->data;
			tmp_l->status = 0;
//			tmp_l->pos = root->all_byte;
			tmp_l->str = tmp2;
			ins->ind[j] = tmp_l;
//			printf("%s   add label 0\n", tmp_l->str);
		}
		else
		{
			ins->ind[j] = tmp_l;
			free(tmp2);
		}
	}
	else if (**str == '-' || (**str >= '0' && **str <= '9'))
	{
		i = ft_atoi_umax(str);
//		if (**str == '-')
//			(*str)++;
		while (*str && **str && **str >= '0' && **str <= '9')
			(*str)++;
//		printf("%s\n", *str);
	}
	else
		ft_close_error(88);
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(46);
	ins->n_com = com->n_com;
	ins->arg[j] = (unsigned int)i;
	ins->byte[j] = IND_SIZE;
	ins->t_dec |= (IND_CODE << (6 - j * 2));
	ins->o_size += IND_SIZE;
}

void		ft_add_command(char *str, t_root *root, t_com *tmp_com)
{
	int		i;
	int		j;

	j = 0;
	i = ft_check_name_command(str, g_com);
	if (i < 0)
		ft_close_error(47);
	str = str + g_com[i].n_sym;
	while (str && *str && (*str == 32 || *str == '\t'))
		str++;
	if (!str || !*str || *str == SEPARATOR_CHAR)
		ft_close_error(35);
	while (j < g_com[i].n_arg)
	{
//		printf("%s\n", str);
		if (str && *str == SEPARATOR_CHAR)
			str++;
		while (str && *str && (*str == 32 || *str == '\t'))
			str++;
		if ((g_com[i].arg[j] & T_REG) && *str == REGISTOR_CHAR)
			ft_check_registor(&str, g_com + i, tmp_com, j);
		else if ((g_com[i].arg[j] & T_DIR) && *str == DIRECT_CHAR)
//			ft_close_error(55);
			ft_check_dir(&str, g_com + i, tmp_com, j, root);
		else if (g_com[i].arg[j] & T_IND)
//			ft_close_error(55);
			ft_check_ind(&str, g_com + i, tmp_com, j, root);
		else
			ft_close_error(37);
		j++;
	}
	tmp_com->o_size++;
	if (g_com[i].t_dec)
		tmp_com->o_size++;
	else
		tmp_com->t_dec = 0;
	tmp_com->a_size = root->all_byte;
	root->all_byte += tmp_com->o_size;

	tmp_com->line = root->line;
//	printf("%zu tmp_com %zu line\n", tmp_com->line, root->line);
//	printf("%lu all_byte\n", root->all_byte);
	if (str && *str)
		ft_close_error(39);
}

void		ft_check_command(int fd, t_root *root)
{
	char	*tmp[4];

	root->line = 0;
	root->instruction = ft_add_next(NULL, ft_creat_node(sizeof(t_com)));
	root->ins_end = root->instruction;
	while (get_next_line(fd, tmp) > 0)
	{
		root->line++;
		tmp[1] = tmp[0];
		if ((tmp[3] = ft_strchr(tmp[0], COMMENT_CHAR)))
			*tmp[3] = '\0';
		if ((tmp[3] = ft_strchr(tmp[0], ALT_COMMENT_CHAR)))
			*tmp[3] = '\0';
		while (tmp[0] && *tmp[0] && (*tmp[0] == 32 || *tmp[0] == '\t'))
			tmp[0]++;
		if (!tmp[0] || !*tmp[0])
		{
			free(tmp[1]);
			continue ;
		}
		ft_check_label(tmp, root);
		while (tmp[0] && *tmp[0] && (*tmp[0] == 32 || *tmp[0] == '\t'))
			tmp[0]++;
		if (!tmp[0] || !*tmp[0])
		{
			free(tmp[1]);
			continue;
		}
		ft_add_command(tmp[0], root, root->ins_end->data);
		root->ins_end = ft_add_next(root->ins_end, ft_creat_node(sizeof(t_com)));
		((t_com*)(root->ins_end->data))->a_size = root->all_byte;
		free(tmp[1]);
	}
	ft_check_last_symbol(root, fd);
}