/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:51:06 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 14:55:40 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_u2(t_type *node, char *str, int i, int minus)
{
	int		len;
	char	*str2;

	len = ((node->width > node->precision) ? node->width : node->precision);
	str2 = ft_strnew(len + 1);
	ft_zerofiller(node, str2, len, &i);
	ft_fillin_num(node, str2, str, len);
	(minus == 0) ? ft_flagminus_num(node, str2, len) : 0;
	write(1, str2, ft_strlen(str2));
	len = ft_strlen(str2);
	free(str2);
	free(str);
	return (len);
}

int			ft_print_u(t_type *node, char *str, int i)
{
	int		len;
	int		minus;

	minus = ft_isnegative(str);
	if (cmp(str, "0") && (node->precision == 0))
		str[0] = '\0';
	if ((node->width != -1 && node->width >= (int)ft_strlen(str) + 1) ||
		(node->precision != -1 && node->precision >= (int)ft_strlen(str) + 1))
	{
		return (ft_print_u2(node, str, i, minus));
	}
	len = ft_strlen(str) + 1;
	(minus == 0) ? ft_flagminus_num(node, str, len) : 0;
	write(1, str, ft_strlen(str));
	len = ft_strlen(str);
	free(str);
	return (len);
}
