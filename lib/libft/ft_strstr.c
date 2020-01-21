/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:42:13 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/06 21:25:25 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;
	size_t	l;

	i = 0;
	l = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i])
	{
		k = 0;
		if (haystack[i] == needle[k])
		{
			while (haystack[i + k] == needle[k] && \
					haystack[i + k] && needle[k])
				k++;
			if (k == l)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
