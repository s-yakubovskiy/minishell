/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:43:54 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 13:20:29 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_swap(char *a, char *b)
{
	char	buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

void			ft_addflag(t_type *node, char flag)
{
	int		i;

	i = 0;
	if (ft_isfl_in(node, flag) == FAIL)
	{
		while (node->type[i] != '\0')
			++i;
		node->type[i] = flag;
	}
}

intmax_t		ft_abs(intmax_t n)
{
	if (n < 0)
		return (-n);
	return (n);
}

unsigned long	ft_nlen(uintmax_t n, int base)
{
	size_t		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n = n / base;
	}
	return (len);
}

void			str2upcase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
}
