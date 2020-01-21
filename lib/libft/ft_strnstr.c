/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:08:04 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/07 16:39:58 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	l;

	i = 0;
	l = ft_strlen(s2);
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i] && i != len)
	{
		k = 0;
		if (s1[i] == s2[k])
		{
			while (s1[i + k] == s2[k] && s1[i + k] \
					&& s2[k] && (i + k) != len)
				k++;
			if (k == l)
				return ((char*)s1 + i);
		}
		i++;
	}
	return (NULL);
}
