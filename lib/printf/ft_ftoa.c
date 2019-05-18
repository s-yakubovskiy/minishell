/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:11:57 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 12:10:36 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*floatpart_maker(double n, int prec, long *intpart)
{
	double	floatpart;
	char	*floatres;
	int		i;

	i = 0;
	if (n == 0.0)
		floatpart = 0.0;
	else if (n > 0.0)
		floatpart = n - (double)(*intpart);
	else
		floatpart = (n * -1) - (double)(*intpart);
	if (prec == 0)
		return (zeroprec(floatpart, *intpart));
	floatres = ft_strnew(prec + 500);
	floatpart += roundgenerator(prec);
	(floatpart >= 1.0) ? (*intpart)++ : 0;
	while (prec > 0)
	{
		floatpart *= 10;
		floatres[i++] = ((int)floatpart == 10) ? '0' : (int)floatpart + '0';
		floatpart -= (int)floatpart;
		prec--;
	}
	floatres[i] = '\0';
	return (floatres);
}

static char		*isconst(double n)
{
	if (n == -1.00 / 0.00)
		return (ft_strdup("-inf"));
	else if (n == 1.00 / 0.00)
		return (ft_strdup("inf"));
	else if (n != n)
		return (ft_strdup("nan"));
	else if (n == 0.0)
		if (*(long*)&n >> 63)
			return (ft_strdup("-0"));
	return (NULL);
}

static char		*retconst(char *frdy, char *ires, char *fres, double n)
{
	if (n == 0.0)
	{
		join_parts(frdy, ires, fres);
		free(ires);
		free(fres);
	}
	return (frdy);
}

char			*ft_ftoa(double n, int afterpoint, t_type *node)
{
	long	intpart;
	char	*intres;
	char	*floatres;
	char	*floatrdy;

	intpart = (n < 0.0) ? (long)n * -1 : (long)n;
	floatres = floatpart_maker(n, afterpoint, &intpart);
	intres = ft_itoa_ll(intpart);
	if ((floatrdy = isconst(n)) != NULL)
		return (retconst(floatrdy, intres, floatres, n));
	if (afterpoint == 0)
	{
		if (n < 0.0)
			return (afterminus(node, floatres, intres));
		(ft_isfl_in(node, '#') == 0) ? sharpmod(floatres) : 0;
		return (floatres);
	}
	floatrdy = malloc(sizeof(char) * ft_strlen(floatres) +
		ft_strlen(intres) + 4);
	join_parts(floatrdy, intres, floatres);
	(n < 0.0) ? ft_flagminus_float(floatrdy, ft_strlen(floatrdy)) : 0;
	free(floatres);
	free(intres);
	return (floatrdy);
}
