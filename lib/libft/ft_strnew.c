/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:52:39 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/09 19:20:04 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*arr;

	if (++size == 0)
		return (NULL);
	if (!(arr = (char*)malloc(size)))
		return (0);
	ft_bzero(arr, size);
	return (arr);
}
