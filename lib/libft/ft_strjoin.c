/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:48:26 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/11 15:01:59 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		if (!(str = (char*)malloc(ft_strlen(s2) + 1)))
			return (NULL);
		return (ft_strcpy(str, s2));
	}
	else if (!s2)
	{
		if (!(str = (char*)malloc(ft_strlen(s1) + 1)))
			return (NULL);
		return (ft_strcpy(str, s1));
	}
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(i + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}
