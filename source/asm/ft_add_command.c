/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:38:38 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/27 14:38:40 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"
#include "../../includes/asm_error.h"

static int	ft_check_name_command(char *str, t_op *com)
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

static void	ft_check_argument(char **str, t_op *com, t_root *root)
{
	int		j;

	j = 0;
	while (j < com->n_arg)
	{
		if (*str && **str == SEPARATOR_CHAR)
			(*str)++;
		while (*str && **str && (**str == 32 || **str == '\t'))
			(*str)++;
		if ((com->arg[j] & T_REG) && **str == REGISTOR_CHAR)
			ft_check_reg(str, root, com, j);
		else if ((com->arg[j] & T_DIR) && **str == DIRECT_CHAR)
			ft_check_dir(str, root, com, j);
		else if (com->arg[j] & T_IND)
			ft_check_ind(str, root, com, j);
		else
			ft_close_error(INVALID_PARAM, root);
		j++;
	}
}

static void	ft_size_byte_ins(t_root *root, t_op *com)
{
	t_com	*tmp_c;

	tmp_c = root->ins_end->data;
	tmp_c->o_size++;
	if (com->t_dec)
		tmp_c->o_size++;
	else
		tmp_c->t_dec = 0;
	tmp_c->a_size = root->all_byte;
	root->all_byte += tmp_c->o_size;
	tmp_c->line = root->line;
}

void		ft_add_command(char *str, t_root *root)
{
	int		i;
	int		j;

	j = 0;
	i = ft_check_name_command(str, g_com);
	if (i < 0)
		ft_close_error(LEXICAL_ERROR, root);
	str = str + g_com[i].n_sym;
	while (str && *str && (*str == 32 || *str == '\t'))
		str++;
	if (!str || !*str || *str == SEPARATOR_CHAR)
		ft_close_error(SYNTAX_ERROR, root);
	ft_check_argument(&str, g_com + i, root);
	ft_size_byte_ins(root, g_com + i);
	if (str && *str)
		ft_close_error(INVALID_PARAM, root);
}
