/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:02:24 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/11 15:41:36 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	n = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	if (i == j + 1)
		return (ft_strnew(0));
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && s[j])
		j--;
	if (!(str = (char*)malloc(j - i + 2)))
		return (NULL);
	while (i != j + 1)
		str[n++] = s[i++];
	str[n] = '\0';
	return (str);
}
