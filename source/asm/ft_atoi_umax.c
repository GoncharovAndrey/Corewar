/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_umax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 08:17:02 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/27 08:17:04 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static unsigned int		ft_res_sign(int z)
{
	if (z > 0)
		return (UINT_MAX);
	else
		return (0);
}


unsigned int			ft_atoi_umax(char **str)
{
	unsigned long int	res;
	unsigned long int	tmp;
	int					z;

	res = 0;
	z = 1;
	tmp = 0;
	if (**str == '-')
	{
		(*str)++;
		z = -1;
	}
	else if (**str > '9' || **str < '0')
		ft_close_error(97);
	while (**str >= '0' && **str <= '9')
	{
//		printf("%lu tmp, %lu res\n", tmp, res);
		if (tmp > res)
			return (ft_res_sign(z));
		tmp = res;
		res = res * 10 + (**str - '0');

		(*str)++;
	}
	return (res * z);
}
