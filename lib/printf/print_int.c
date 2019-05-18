/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:59:49 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 15:32:57 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_freenode(t_type *node)
{
	free(node->type);
	free(node->flags);
	free(node);
}

int			ft_print_int2(t_type *node, char *str, int minus)
{
	int		len;

	len = ft_strlen(str) + 1;
	(ft_isfl_in(node, ' ') == 0 ||
		ft_isfl_in(node, '+') == 0) ? ft_flagsp_num(str, len) : 0;
	(minus == 0) ? ft_flagminus_num(node, str, len) : 0;
	ft_flagplus_num(node, str, minus, len);
	write(1, str, ft_strlen(str));
	len = ft_strlen(str);
	free(str);
	return (len);
}

int			ft_print_int3(t_type *node, char *str, int i, int minus)
{
	int		len;
	char	*str2;

	node->zero = (cmp(str, "0") == 1);
	len = ((node->width > node->precision) ? node->width : node->precision);
	str2 = ft_strnew(len + 1);
	ft_zerofiller(node, str2, len, &i);
	ft_fillin_num(node, str2, str, len);
	if (ft_isfl_in(node, '-') == -1 && ft_isfl_in(node, ' ') == 0 &&
		ft_isfl_in(node, '0') == 0 && node->precision == -1)
		str2[0] = ' ';
	(node->precision < node->width && ft_isfl_in(node, '-') == -1) ?
	turnoff_fl(node->flags, ' ') : 0;
	(ft_isfl_in(node, ' ') == 0) ? ft_flagsp_num(str2, len) : 0;
	(minus == 0) ? ft_flagminus_num(node, str2, len) : 0;
	ft_flagplus_num(node, str2, minus, len);
	len = (node->width > node->precision) ? node->width : node->precision;
	if (len < (int)ft_strlen(str2) && str2[ft_strlen(str2) - 1] == ' ')
		str2[len] = '\0';
	len = ft_strlen(str2);
	write(1, str2, ft_strlen(str2));
	free(str2);
	free(str);
	return (len);
}

int			ft_print_int(t_type *node, char *str, int i)
{
	int		minus;

	minus = ft_isnegative(str);
	if (cmp(str, "0") && (node->precision == 0))
		str[0] = '\0';
	if ((node->width != -1 && node->width >= (int)ft_strlen(str) + 1) ||
		(node->precision != -1 && node->precision >= (int)ft_strlen(str) + 1))
	{
		return (ft_print_int3(node, str, i, minus));
	}
	return (ft_print_int2(node, str, minus));
}
