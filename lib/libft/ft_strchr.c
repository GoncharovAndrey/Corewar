/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:02:26 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/06 20:20:06 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c_in)
{
	char	*str;

	str = (char*)s;
	while (*str != c_in)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return (str);
}
