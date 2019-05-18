/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:43:54 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 13:06:29 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		join_parts(char *floatrdy, char *intres, char *floatres)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(floatrdy) > 0 ? ft_strlen(floatrdy) - 1 : 0;
	while (intres[i] != '\0')
	{
		floatrdy[j] = intres[i];
		i++;
		j++;
	}
	i = 0;
	floatrdy[j++] = '.';
	while (floatres[i] != '\0')
	{
		floatrdy[j] = floatres[i];
		i++;
		j++;
	}
	floatrdy[j] = '\0';
}

void		ft_flagminus_float(char *str, int len)
{
	int		i;

	i = 0;
	str[len] = '\0';
	str[len + 1] = '\0';
	if (ft_isdigit(str[0]))
	{
		len -= (str[ft_strlen(str) - 1] == ' ') ? 1 : 0;
		while (len > 0)
		{
			ft_swap(&str[len], &str[len - 1]);
			--len;
		}
		str[len] = '-';
	}
	else
	{
		while (str[i] == ' ' && str[i] != '0' && str[i] != '\0')
			i++;
		str[i - 1] = '-';
	}
}

void		sharpmod(char *floatrdy)
{
	int		len;

	len = ft_strlen(floatrdy);
	floatrdy[len] = '.';
}

char		*afterminus(t_type *node, char *fres, char *intres)
{
	char	*floatrdy;

	floatrdy = ft_strnew(ft_strlen(fres) + 6);
	floatrdy = ft_strcat(floatrdy, fres);
	ft_flagminus_float(floatrdy, ft_strlen(floatrdy));
	(ft_isfl_in(node, '#') == 0) ? sharpmod(floatrdy) : 0;
	free(fres);
	free(intres);
	return (floatrdy);
}
