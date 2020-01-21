/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:46:30 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/07 17:19:50 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const	char *s1, const char *s2)
{
	unsigned char	*s1_c;
	unsigned char	*s2_c;

	s1_c = (unsigned char*)s1;
	s2_c = (unsigned char*)s2;
	while (*s1_c == *s2_c && *s1_c && *s2_c)
	{
		s1_c++;
		s2_c++;
	}
	return (*s1_c - *s2_c);
}
