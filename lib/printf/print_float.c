/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:36:54 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 12:51:30 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_print_fconst2(t_type *node, char *str, int i, int minus)
{
	char	*str2;
	int		len;

	len = node->width;
	str2 = ft_strnew(len);
	ft_zerofiller2(node, str2, len, &i);
	ft_fillin_num(node, str2, str, len);
	((ft_isfl_in(node, ' ') == 0) || (ft_isfl_in(node, '+') == 0)) &&
		str2[0] != ' ' && (ft_isfl_in(node, ' ') == 0) &&
		ft_strcmp(str, "nan") != 0 ? ft_flagsp_num(str2, len) : 0;
	ft_flagplus_num(node, str2, minus, len);
	if (cmp(node->type, "F") || cmp(node->type, "lF") ||
		cmp(node->type, "LF"))
		str2upcase(str2);
	if (len < (int)ft_strlen(str2) && str2[ft_strlen(str2) - 1] == ' ')
		str2[len] = '\0';
	write(1, str2, ft_strlen(str2));
	free(str2);
	free(str);
	return (len);
}

int			ft_print_fconst(t_type *node, char *str, int i)
{
	int		len;
	int		minus;

	minus = ft_isnegative2(str);
	if (str[0] == '-' || ft_isfl_in(node, '+') == 0)
		turnoff_fl(node->flags, ' ');
	if ((node->width != -1 && node->width >= (int)ft_strlen(str) + 1))
		return (ft_print_fconst2(node, str, i, minus));
	len = ft_strlen(str) + 1;
	ft_flagsp_num(str, len);
	if (cmp(node->type, "F") || cmp(node->type, "lF") || cmp(node->type, "LF"))
		str2upcase(str);
	ft_flagplus_num(node, str, minus, len);
	write(1, str, ft_strlen(str));
	free(str);
	return (len);
}

int			ft_print_float3(t_type *node, char *str2)
{
	int		len;

	len = (node->width > node->precision) ? node->width : node->precision;
	if (len < (int)ft_strlen(str2) && str2[ft_strlen(str2) - 1] == ' ')
		str2[len] = '\0';
	len = ft_strlen(str2);
	write(1, str2, ft_strlen(str2));
	free(str2);
	return (len);
}

int			ft_print_float2(t_type *node, char *str, int minus)
{
	char	*str2;
	int		len;
	int		i;

	i = 0;
	node->zero = (cmp(str, "0") == 1 || cmp(str, "0.") == 1);
	len = ((node->width > (int)ft_strlen(str)) ? node->width :
		ft_strlen(str));
	str2 = ft_strnew(len + 3);
	ft_zerofiller(node, str2, len, &i);
	ft_zerofiller3(node, str2, len, 0);
	ft_fillin_num(node, str2, str, len);
	(node->precision < node->width && ft_isfl_in(node, '-') == -1) ?
		turnoff_fl(node->flags, ' ') : 0;
	(ft_isfl_in(node, ' ') == 0) ? ft_flagsp_num(str2, len) : 0;
	if ((minus == 0 && str2[0] == '0' && node->zero == 0) ||
		(ft_isfl_in(node, '+') == 0 && ft_isfl_in(node, '0') == 0))
		str2[0] = '-';
	else if (minus == 0)
		ft_flagminus_num(node, str2, len);
	ft_flagplus_num(node, str2, minus, len);
	free(str);
	return (ft_print_float3(node, str2));
}

int			ft_print_float(t_type *node, double n, int i)
{
	int		len;
	int		minus;
	char	*str;

	str = ft_ftoa(n, (((node->precision) == -1) ? 6 : node->precision), node);
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
