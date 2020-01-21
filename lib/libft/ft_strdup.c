/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:13:52 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/05 20:54:21 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	lenght;

	lenght = ft_strlen(s);
	if (!(result = (char*)malloc(sizeof(char) * (lenght + 1))))
		return (NULL);
	lenght = 0;
	while (s[lenght])
	{
		result[lenght] = s[lenght];
		lenght++;
	}
	result[lenght] = '\0';
	return (result);
}
