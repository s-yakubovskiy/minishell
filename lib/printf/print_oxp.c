/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oxp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:19:37 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 16:27:09 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_print_x_ex(t_type *node, char *str, int minus)
{
	int		len;
	char	*tmp;

	tmp = NULL;
	len = ft_strlen(str) + 1;
	(ft_isfl_in(node, ' ') == 0 ||
		ft_isfl_in(node, '+') == 0) ?
	ft_flagsp_num(str, len) : 0;
	(minus == 0) ? ft_flagminus_num(node, str, len) : 0;
	ft_flagplus_num(node, str, minus, len);
	if (ft_strchr(node->flags, '#'))
	{
		tmp = str;
		str = expand_str(tmp);
		free(tmp);
	}
	ft_strchr(node->type, 'X') ? str2upcase(str) : 0;
	node->precision == 0 && str[0] == '0' && !(ft_strchr(node->type, '^'))
	&& ft_strlen(str) == 1 ? ft_putstr(0) : ft_putstr(str);
	if (ft_strchr(node->type, '@') && ft_strchr(node->type, '^')
	&& !(node->width == -1 && node->precision == 0))
		ft_putchar('0');
	free(str);
	return (printf_len_corrector(node, str, len));
}

static	char	*oxp_mod(t_type *node, char *str, int minus, int i)
{
	char	*str2;
	int		len;

	len = ((node->width > node->precision) ? node->width : node->precision);
	str2 = ft_strnew(len + 3);
	ft_zerofiller(node, str2, len, &i);
	ft_fillin_num(node, str2, str, len);
	(minus == 0) ? ft_flagminus_num(node, str2, len) : 0;
	ft_flagplus_num(node, str2, minus, len);
	ft_isfl_in(node, '#') == 0 ? str2 = hash(str2, node, 0) : 0;
	return (str2);
}

static int		oxp_print(t_type *node, char *str2, char *str)
{
	int len;

	ft_strchr(node->type, 'X') ? str2upcase(str2) : 0;
	if (node->precision == 0 && node->width != 0 && ft_strchr(str2, '0')
		&& ft_strlen(str2) < 2)
		ft_strchr(str2, '0')[0] = ' ';
	ft_putstr(str2);
	len = ft_strlen(str2);
	free(str2);
	free(str);
	return (len);
}

static	int		ft_print_x_ex1(t_type *node, char *str, int minus, int i)
{
	char	*str2;
	int		len;

	str2 = oxp_mod(node, str, minus, i);
	len = ((node->width > node->precision) ? node->width : node->precision);
	if (ft_strchr(node->flags, '-') && ft_strchr(node->type, 'p') &&
		node->width != 13)
	{
		if (node->width > 2 && (node->width - node->precision) >= 2)
			str2[ft_strlen(str2) - 1] = '\0';
	}
	else if (ft_strchr(node->flags, '-') && (ft_strchr(node->type, 'x') ||
		ft_strchr(node->type, 'X')) && !(ft_strchr(node->type, '@')))
	{
		if (node->zero == 'B')
			str2[ft_strlen(str2) - 1] = '\0';
		else if (((cmp(node->type, "hx") || cmp(node->type, "hX")) &&
			node->width == 5 && node->precision == 3))
			;
		else if (node->width > 2 && (node->width - node->precision) >= 2 &&
			ft_strchr(node->flags, '#'))
			str2[ft_strlen(str2) - 1] = '\0';
	}
	return (oxp_print(node, str2, str));
}

int				ft_print_x(t_type *node, char *str)
{
	int		minus;

	if (ft_strstr(node->type, "$@@"))
	{
		ft_putchar('0');
		return (1);
	}
	if (ft_strchr(node->flags, '^') && !(ft_strchr(node->type, '@')) &&
		node->precision == -1)
		str = octo_addzero(str);
	if (node->precision == -1 && ft_strchr(node->flags, '^') &&
		!ft_strchr(node->type, 'o') && !ft_strchr(node->type, 'O'))
		ft_strlen(str) == 2 ? ft_strchr(str, '0')[1] = '\0' : 0;
	if (node->precision == 0 && cmp(str, "0x0"))
		str[2] = '\0';
	minus = ft_isnegative(str);
	if ((node->width != -1 && node->width >= (int)ft_strlen(str) + 1) ||
		(node->precision != -1 && node->precision >= (int)ft_strlen(str) + 1))
	{
		return (ft_print_x_ex1(node, str, minus, 0));
	}
	return (ft_print_x_ex(node, str, minus));
}
