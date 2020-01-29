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

char			*ft_create_name(char *av)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_strdup(av);
	tmp = ft_strrchr(tmp2, '.');
	tmp++;
	if (!tmp || *tmp != 's' || *(tmp + 1))
		ft_close_error(7);
	tmp--;
	*tmp = '\0';
	tmp = tmp2;
	if (!(tmp2 = ft_strjoin(tmp2, ".cor")))
		ft_close_error(995);
	free(tmp);
	return (tmp2);
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
