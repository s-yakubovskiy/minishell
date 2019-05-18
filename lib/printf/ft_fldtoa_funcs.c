/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fldtoa_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:11:57 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 12:11:24 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*zeroprec(double floatpart, long res)
{
	if (floatpart == 0.00)
		return (ft_itoa_ll(res));
	else if (res % 2 == 0)
	{
		if (floatpart > 0.50000000000000000)
			return (ft_itoa_ll(res + 1));
		else if (floatpart < 0.50000000000000000 ||
			floatpart == 0.5000000000000000)
			return (ft_itoa_ll(res));
	}
	else
	{
		if (floatpart > 0.50000000000000000 || floatpart == 0.50000000000000000)
		{
			return (ft_itoa_ll(res + 1));
		}
		else if (floatpart < 0.50000000000000000)
			return (ft_itoa_ll(res));
	}
	return (ft_strdup("sw"));
}

double		roundgenerator(int prec)
{
	int		i;
	double	round;

	i = 0;
	round = 0.5;
	while (i < prec)
	{
		round /= 10;
		i++;
	}
	return (round);
}

char		*zeroprec2(long double floatpart, long res)
{
	if (floatpart == 0.00)
		return (ft_itoa_ll(res));
	else if (res % 2 == 0)
	{
		if (floatpart > 0.50000000000000000)
			return (ft_itoa_ll(res + 1));
		else if (floatpart < 0.50000000000000000 ||
			floatpart == 0.5000000000000000)
			return (ft_itoa_ll(res));
	}
	else
	{
		if (floatpart > 0.50000000000000000 || floatpart == 0.50000000000000000)
		{
			return (ft_itoa_ll(res + 1));
		}
		else if (floatpart < 0.50000000000000000)
			return (ft_itoa_ll(res));
	}
	return (ft_strdup("sw"));
}

long double	roundgenerator2(int prec)
{
	int			i;
	long double	round;

	i = 0;
	round = 0.5;
	while (i < prec)
	{
		round /= 10;
		i++;
	}
	return (round);
}
