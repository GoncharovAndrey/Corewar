/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:49:49 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/13 17:49:53 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word(const char *s, char c)
{
	int		word;

	word = 0;
	if (*s != c && *s)
	{
		s++;
		word++;
	}
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s != c && *s)
				word++;
		}
		s++;
	}
	return (word);
}

static int	ft_len(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	int		j;
	int		i;
	char	**spt;

	j = 0;
	i = 0;
	if (!s || !(spt = (char**)malloc(sizeof(char *) * (ft_word(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!(spt[j] = (char*)malloc(sizeof(char) * (ft_len(s, c) + 1))))
				return (NULL);
			while (*s && *s != c)
				spt[j][i++] = (char)*s++;
			spt[j][i] = '\0';
			j++;
			i = 0;
		}
	}
	spt[j] = NULL;
	return (spt);
}
