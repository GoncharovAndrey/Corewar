/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:49:10 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/05 20:53:43 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	lenght;

	lenght = ft_strlen(src);
	if (lenght < n)
	{
		while (lenght != n)
			dest[lenght++] = '\0';
		lenght = 0;
		while (src[lenght])
		{
			dest[lenght] = src[lenght];
			lenght++;
		}
	}
	else
	{
		lenght = 0;
		while (lenght != n)
		{
			dest[lenght] = src[lenght];
			lenght++;
		}
	}
	return (dest);
}
