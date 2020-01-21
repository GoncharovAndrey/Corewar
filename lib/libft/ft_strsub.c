/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:18:44 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/11 13:48:04 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	i;

	i = 0;
	if (!s || !*(s + start))
		return (NULL);
	if (!(copy = ft_strnew(len)))
		return (NULL);
	while (s && i != len)
	{
		copy[i] = s[start + i];
		i++;
	}
	return (copy);
}
