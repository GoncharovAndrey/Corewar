/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 10:34:46 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/24 10:34:48 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_dlist		*ft_creat_node(size_t size)
{
	t_dlist	*tmp;

	if (!(tmp = (t_dlist*)malloc(sizeof(t_dlist))))
		ft_close_error(127);
	if (!(tmp->data = (void*)malloc(size)))
		ft_close_error(127);
	ft_memset(tmp->data, 0, size);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_dlist		*ft_add_next(t_dlist *node, t_dlist *tmp)
{
	if (!node)
		return (tmp);
	if (!tmp)
		return (node);
	if (node->next)
		return (NULL);
	node->next = tmp;
	tmp->prev = node;
	return (tmp);
}

t_dlist		*ft_cut_dlist(t_dlist *del, t_dlist **head)
{
	if (del->next)
		del->next->prev = del->prev;
	if (del->prev)
		del->prev->next = del->prev;
	if (!del->next && !del->prev)
		*head = NULL;
	return (del);
}

t_dlist		*ft_add_prev(t_dlist *node, t_dlist *tmp)
{
	if (!node)
		return (tmp);
	if (!tmp)
		return (node);
	if (node->next)
		return (NULL);
	node->prev = tmp;
	tmp->next = node;
	return (tmp);
}