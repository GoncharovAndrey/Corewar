/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:48:41 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/08 14:45:14 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, \
		int c, size_t n)
{
	void *p;

	p = ft_memchr(src, c, n);
	if (p != NULL)
		return (ft_memcpy(dst, src, p - src + 1) + (p - src + 1));
	ft_memcpy(dst, src, n);
	return (NULL);
}
