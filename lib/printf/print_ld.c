/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 09:33:38 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 12:51:05 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_print_ld(t_type *node, long double n, int i)
{
	int		len;
	int		minus;
	char	*str;

	str = ft_ldtoa(n, (((node->precision) == -1) ? 6 : node->precision), node);
	if (is_const(str) == SUCCESS)
		return (ft_print_fconst(node, str, i));
	minus = ft_isnegative(str);
	if ((node->width != -1 && node->width >= (int)ft_strlen(str) + 1))
		return (ft_print_float2(node, str, minus));
	len = ft_strlen(str) + 1;
	(ft_isfl_in(node, ' ') == 0 || ft_isfl_in(node, '+') == 0) ?
	ft_flagsp_num(str, len) : 0;
	(minus == 0) ? ft_flagminus_num2(str, len) : 0;
	ft_flagplus_num(node, str, minus, len);
	write(1, str, ft_strlen(str));
	len = ft_strlen(str);
	free(str);
	return (len);
}
