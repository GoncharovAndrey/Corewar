/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:18:52 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/08 17:36:19 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_d;
	const unsigned char	*c_s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	c_d = dst;
	c_s = src;
	i = 0;
	if (c_d > c_s && (size_t)(c_d - c_s) < len)
		while (len--)
			c_d[len] = c_s[len];
	else
	{
		i = 0;
		while (i < len)
		{
			c_d[i] = c_s[i];
			i++;
		}
	}
	return (dst);
}
