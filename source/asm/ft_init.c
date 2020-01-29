/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 09:53:27 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/29 09:53:29 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include "../../includes/asm_g_com.h"
#include "../../includes/asm_error.h"

char			*ft_create_name(char *av, t_root *root)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_strdup(av);
	if (!(tmp = ft_strrchr(tmp2, '.')))
		ft_close_error(OPEN_ERROR, root);
	tmp++;
	if (!tmp || *tmp != 's' || *(tmp + 1))
		ft_close_error(OPEN_ERROR, root);
	tmp--;
	*tmp = '\0';
	tmp = tmp2;
	if (!(tmp2 = ft_strjoin(tmp2, ".cor")))
		ft_close_error(MALLOC_ERROR, NULL);
	free(tmp);
	return (tmp2);
}

void			ft_init_root(t_root **root)
{
	if (!((*root) = ft_memalloc(sizeof(t_root))))
		ft_close_error(MALLOC_ERROR, NULL);
	if (!((*root)->header = ft_memalloc(sizeof(t_header))))
		ft_close_error(MALLOC_ERROR, NULL);
	if (!((*root)->lbl_char = ft_strjoin(LABEL_CHARS, NULL)))
		ft_close_error(MALLOC_ERROR, NULL);
	(*root)->line = 0;
	(*root)->header->magic = COREWAR_EXEC_MAGIC;
	ft_bzero((*root)->fd, sizeof(int) * 2);
}

void			ft_del_root(t_root **root)
{
	if (!*root)
		return ;
	if ((*root)->header)
		free((*root)->header);
	if ((*root)->lbl_char)
		free((*root)->lbl_char);
	if ((*root)->instruction)
		ft_del_dlist_next((*root)->instruction);
	if ((*root)->label)
		ft_del_dlist_prev((*root)->label);
	if ((*root)->name)
		free((*root)->name);
	free((*root));
}
