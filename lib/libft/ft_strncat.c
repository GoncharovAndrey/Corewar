/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:17:41 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/12 17:32:33 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	index;
	size_t	index_2;

	index = 0;
	while (src[index] && index != n)
		index++;
	index_2 = ft_strlen(dest);
	n = index + index_2;
	index = 0;
	while (index_2 != n)
	{
		dest[index_2] = src[index];
		index_2++;
		index++;
	}
	dest[index_2] = '\0';
	return (dest);
}
