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

void		ft_check_char(char *str, char *check)
{
	char	*tmp;

	while (str && *str != LABEL_CHAR)
	{
		tmp = check;
		while (tmp && *tmp)
		{
			if (*str == *tmp)
				break;
			tmp++;
		}
		if (!*tmp)
			ft_close_error(75);
		str++;
	}
}

void			ft_put_values(t_dlist *head, unsigned long int size)
{
	t_dlist		*tmp;
	t_com		*tmp_c;

	tmp = head;
	while (tmp)
	{
		tmp_c = (t_com*)tmp->data;
		if (tmp_c->arg[3] & 1)
			tmp_c->arg[0] = size - tmp_c->a_size;
		if (tmp_c->arg[3] & 2)
			tmp_c->arg[1] = size - tmp_c->a_size;
		if (tmp_c->arg[3] & 4)
			tmp_c->arg[2] = size - tmp_c->a_size;
		tmp = tmp->next;
	}
}

t_label		ft_find_label(char *str, t_dlist *label)
{
	t_dlist	*tmp;
	t_label	*tmp_l;

	tmp = label;
	while (tmp)
	{
		tmp_l = (t_label*)label->data;
		if (ft_strcmp(tmp_l->str, str) == 0)
			return (tmp_l);
		tmp = tmp->next;
	}
	return (NULL);
}

void		ft_check_label(char *str, t_root *root, t_com *com)
{
	t_label	*tmp_l;

	ft_check_char(str, root->lbl_char);
	if (!(tmp_l = ft_find_label(str, root->label))
	{
		root->label = ft_add_prev(root->label, ft_creat_node(sizeof(t_label)));
		tmp_l = (t_label*)root->label->data;
		tmp_l->status = 1;
		tmp_l->pos = com->a_size;
		return;
	}
	if (tmp_l->status == 0)
	{
		tmp_l->pos = com->a_size;
		ft_put_values(tmp_l->head, tmp_l->pos);
		tmp_l->status = 1;
	}
}

int			ft_check_name_command(char *str, t_op *com)
{
	int		i;

	i = 0;
	while (com[i].n_com)
	{
		if (ft_strncmp(str, com[i].name, com[i].n_sym) == 0)
			return (i);
		i++;
	}
	return (-1);
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
	printf("%s\n", *str);
	while (*str && **str && (**str == 32 || **str == '\t'))
		(*str)++;
	if (*str && **str && **str != SEPARATOR_CHAR)
		ft_close_error(44);
	ins->n_com = com->n_com;
	ins->arg[j] = (unsigned int)i;
	ins->t_dec = REG_CODE << (6 - j * 2);
	ins->o_size++;
}


void		ft_check_ind(char **str, t_op *com, t_com *ins, int j)
{
	unsigned long int	i;
	t_label				tmp_l;

	i = 0;
	if (**str == LABEL_CHAR)
	{
		(*str)++;
		tmp_l = ft_find_label(*str,)

	}
	else if (**str == '-' || (**str >= '0' && **str <= '9'))
	{
		i = ft_atoi(str);
		if (**str == '-')
			(*str)++;
		while (*str && **str && **str >= '0' && **str <= '9')
			(*str)++;
		printf("%s\n", *str);
		while (*str && **str && (**str == 32 || **str == '\t'))
			(*str)++;
		if (*str && **str && **str != SEPARATOR_CHAR)
			ft_close_error(44);
	}
	else
		ft_close_error(88);
	ins->n_com = com->n_com;
	ins->arg[j] = (unsigned int)i;
	ins->t_dec = IND_CODE << (6 - j * 2);
	ins->o_size += 2;
}



void		ft_add_command(char *str, t_root *root, t_com *tmp_com)
{
	int		i;
	int		j;

	j = 0;
	i = ft_check_name_command(str, root->commmand);
	if (i < 0)
		ft_close_error(44);
	str = str + root->commmand[i].n_sym;
	while (str && *str && (*str == 32 || *str == '\t'))
		str++;
	if (!str || !*str || *str == SEPARATOR_CHAR)
		ft_close_error(33);
	while (j < root->commmand[i].n_arg)
	{
		printf("%s\n", str);
		if (str && *str == SEPARATOR_CHAR)
			str++;
		while (str && *str && (*str == 32 || *str == '\t'))
			str++;
		if ((root->commmand[i].arg[j] & T_REG) && *str == REGISTOR_CHAR)
			ft_check_registor(&str, root->commmand + i, tmp_com, j);
		else if ((root->commmand[i].arg[j] & T_DIR) && *str == DIRECT_CHAR)
			ft_close_error(55);
			//			ft_check_dir(str, tmp_com);
		else if (root->commmand[i].arg[j] & T_IND)
			ft_close_error(55);
//			ft_chech_ind(str, tmp_com);
		else
			ft_close_error(33);
		j++;
	}
	tmp_com->o_size++;
	if (root->commmand[i].t_dec)
		tmp_com->o_size++;
	else
		tmp_com->t_dec = 0;
	tmp_com->a_size = tmp_com->a_size + tmp_com->o_size;
	if (str && *str)
		ft_close_error(33);
}

void		ft_check_command(int fd, t_root *root)
{
	char	*tmp[4];
	t_dlist	*tmp_com;

	root->instruction = ft_add_next(NULL, ft_creat_node(sizeof(t_com)));
	tmp_com = root->instruction;
	while (get_next_line(fd, tmp) > 0)
	{
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
		if ((tmp[3] = ft_strchr(tmp[0], LABEL_CHAR)))
		{
			ft_check_label(tmp[0], root,(t_com*)(tmp_com->data));
			tmp[0] = tmp[3] + 1;
		}
		while (tmp[0] && *tmp[0] && (*tmp[0] == 32 || *tmp[0] == '\t'))
			tmp[0]++;
		if (!tmp[0] || !*tmp[0])
		{
			free(tmp[1]);
			continue;
		}
		ft_add_command(tmp[0], root, tmp_com->data);
		tmp_com = ft_add_next(tmp_com, ft_creat_node(sizeof(t_com)));
		free(tmp[1]);
	}
}