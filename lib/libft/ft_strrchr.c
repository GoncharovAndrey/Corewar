/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:42:04 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/06 20:22:47 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*position;
	char	*found;

	if (c == 0)
		return (ft_strchr(s, '\0'));
	found = NULL;
	while ((position = ft_strchr(s, c)) != NULL)
	{
		found = position;
		s = position + 1;
	}
	return (found);
}
