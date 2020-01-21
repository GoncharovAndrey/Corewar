/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:58:28 by cjosue            #+#    #+#             */
/*   Updated: 2019/09/12 12:55:39 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_single(long int *num)
{
	if (*num < 0)
	{
		*num = *num * -1;
		return (1);
	}
	else
		return (0);
}

char		*ft_itoa(int n)
{
	char			*res;
	int				i;
	long int		num;
	int				f;

	num = n;
	i = 1;
	f = ft_single(&num);
	i += f;
	while ((n / 10) != 0)
	{
		i++;
		n /= 10;
	}
	if (!(res = ft_strnew(i)))
		return (NULL);
	while (--i >= (0 + f))
	{
		res[i] = num % 10 + '0';
		num = num / 10;
	}
	if (f == 1)
		res[0] = '-';
	return (res);
}
