/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:29:55 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/26 17:29:57 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"


void		ft_write_number(void *num, int byte, int fd)
{
	while (--byte >= 0)
		write(fd, num + byte, 1);
}


void		ft_write_header(t_header *header, int fd)
{
	unsigned int	i;

	i = 0;
	ft_write_number(&header->magic, 4, fd);
	write(fd, header->prog_name, PROG_NAME_LENGTH);
	write(fd, &i, 4);
	ft_write_number(&header->prog_size, 4, fd);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, &i, 4);
}


void		ft_write_token(t_com *token, int fd)
{
	int		i;

	i = 0;
	write(fd, &token->n_com, 1);
	if (token->t_dec)
		write(fd, &token->t_dec, 1);
	while (i < 3)
	{
		if (token->ind[i])
			token->arg[i] = token->ind[i]->pos - token->a_size;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (token->byte[i])
			ft_write_number(&token->arg[i] , token->byte[i], fd);
		i++;
	}
}


void		ft_write_cor(t_root *root, int	fd)
{
	t_dlist	*tmp;

	tmp = root->instruction;
	ft_write_header(root->header, fd);
	while (tmp)
	{
		ft_write_token(tmp->data, fd);
		tmp = tmp->next;
	}
}
