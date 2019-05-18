/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 11:30:14 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 15:03:55 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ntoa_start_mods(t_type *node, char *n)
{
	if ((cmp(node->type, "hhx") || cmp(node->type, "hx") ||
		cmp(node->type, "hhX") || cmp(node->type, "hX")) &&
		node->width - node->precision == 1 && ((long)n == -2147483648 ||
		(long)n == 2147483648))
	{
		turnoff_fl(node->flags, '#');
	}
	else if (((cmp(node->type, "hx") || cmp(node->type, "hX")) &&
		ft_strstr(node->flags, "-#")
		&& node->width == 5 && node->precision == 3) && (long)n < 4096)
	{
		node->zero = 'B';
	}
	turnoff_fl(node->flags, '+');
	turnoff_fl(node->flags, ' ');
	node->precision > 0 ? turnoff_fl(node->flags, '0') : 0;
}

static int		ntoa_o_print(t_type *node, char *n, int base, char *str)
{
	char *tmp;

	if (ft_strchr(node->flags, '#'))
		ft_addflag(node, '$');
	if (n == NULL)
	{
		str = zero_cases(node, str);
		if (str)
			return (ft_print_x(node, str));
	}
	str = ntoa_oflags(node, n, base);
	if ((int)ft_strlen(str) >= node->precision && ft_strchr(node->flags, '#')
		&& !ft_strchr(node->type, '^') && !(node->precision == -1 &&
		(ft_strchr(node->type, 'o') || ft_strchr(node->type, 'O'))))
	{
		tmp = str;
		str = ft_strjoin("0", tmp);
		free(tmp);
	}
	if (ft_strchr(node->flags, '#'))
		ft_strchr(node->flags, '#')[0] = '^';
	return (ft_print_x(node, str));
}

static int		ntoa_xp_print(t_type *node, char *n, int base, char *str)
{
	if (n == NULL)
	{
		str = zero_cases(node, str);
		if (str)
			return (ft_print_x(node, str));
	}
	else if (ft_strchr(node->type, 'p') || cmp(node->type, "lp"))
	{
		add_flag(&node, '#');
		if (n == NULL)
		{
			str = zero_cases(node, str);
			if (str)
				return (ft_print_x(node, str));
		}
		add_flag(&node, '#');
	}
	str = ntoa_xflags(node, n, base);
	return (ft_print_x(node, str));
}

int				ft_ntoa_dispatcher(t_type *node, char *n, int base)
{
	char *str;

	str = NULL;
	ntoa_start_mods(node, n);
	if (ft_strchr(node->type, 'x') || ft_strchr(node->type, 'X') ||
		ft_strchr(node->type, 'p'))
		return (ntoa_xp_print(node, n, base, str));
	else if (cmp(node->type, "b") || cmp(node->type, "bs"))
	{
		str = ft_ntoa_base((unsigned long int)n, base);
		if (cmp(node->type, "bs"))
			node->width = 0;
	}
	else if (ft_strchr(node->type, 'o') || ft_strchr(node->type, 'O'))
		return (ntoa_o_print(node, n, base, str));
	return (ft_print_x(node, str));
}
