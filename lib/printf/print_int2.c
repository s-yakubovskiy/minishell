/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:52:52 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 14:53:00 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	istype(char *str)
{
	const char	base[][4] = { "u", "lu", "llu", "hu", "hhu", "x", "X",
								"o", "O", "" };
	int			i;

	i = 0;
	while (cmp((char *)base[i], "") != SUCCESS)
	{
		if (cmp((char *)base[i], str))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_flagplus_num2(t_type *node, char *str, int len)
{
	(str[len - 1] == ' ') ? str[len - 1] = '\0' : 0;
	if (ft_isfl_in(node, '+') == 0 && ft_isfl_in(node, '0') == 0 &&
		(node->precision == -1 || node->width > 0))
		str[0] = '+';
	else
	{
		while (len > 0 && (ft_isdigit(str[0]) == 1 || node->width == -1
			|| node->precision != -1 || node->zero == 1))
		{
			ft_swap(&str[len], &str[len - 1]);
			--len;
		}
		str[0] = ((istype(node->type)) ? ' ' : '+');
	}
}

void		ft_flagplus_num(t_type *node, char *str, int minus, int len)
{
	int		i;

	i = 0;
	if (ft_strstr(str, "nan"))
		return ;
	if (ft_isfl_in(node, '+') == 0 && minus == -1)
	{
		if (ft_isdigit(str[0]) || str[0] == 'i')
		{
			ft_flagplus_num2(node, str, len);
		}
		else
		{
			while (str[i] == ' ' && str[i] != '\0')
				++i;
			str[(i == 0) ? 0 : i - 1] = ((istype(node->type)) ? ' ' : '+');
		}
	}
}

void		ft_flagminus_num(t_type *node, char *str, int len)
{
	int		i;

	i = 0;
	if (str[0] == '0' && node->precision == -1)
		str[0] = '-';
	else if (ft_isdigit(str[0]))
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
