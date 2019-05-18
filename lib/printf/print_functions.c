/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:29:14 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 16:36:53 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			cmp(char *type, char *c)
{
	return ((ft_strcmp(type, c) == 0) ? 1 : 0);
}

static int	ft_print_dispatcher3(t_type *n, char *t, va_list args)
{
	if (cmp(t, "b"))
		return (ft_ntoa_dispatcher(n, va_arg(args, char*), 2));
	else if (cmp(t, "bs"))
		return (ft_ntoa_dispatcher(n, va_arg(args, char*), n->width));
	else if (cmp(t, "%"))
		return (ft_print_char(n, '%', 0));
	else if (ft_strchr(t, 'o') || ft_strchr(t, 'O'))
		return (ft_ntoa_dispatcher(n, va_arg(args, char*), 8));
	else if (cmp(t, "clr"))
		return (print_color_string(n, va_arg(args, char *), 0, n->precision));
	return (0);
}

static int	ft_print_dispatcher2(t_type *node, char *t, va_list args)
{
	if (cmp(t, "jd") || cmp(t, "ji") || cmp(t, "jD") || cmp(t, "zD"))
		return (ft_print_int(node, ft_itoa_im(va_arg(args, intmax_t)), 0));
	else if (cmp(t, "u"))
		return (ft_print_u(node, ft_itoa_ui(va_arg(args, unsigned int)), 0));
	else if (cmp(t, "ju") || cmp(t, "jU"))
		return (ft_print_u(node, ft_itoa_uim(va_arg(args, uintmax_t)), 0));
	else if (cmp(t, "hu"))
		return (ft_print_u(node, ft_itoa_uh(va_arg(args, int)), 0));
	else if (cmp(t, "hhu"))
		return (ft_print_u(node, ft_itoa_uhh(va_arg(args, int)), 0));
	else if (cmp(t, "lu") || cmp(t, "llu") || cmp(t, "U") || cmp(t, "hU") ||
		cmp(t, "hhU") || cmp(t, "lU") || cmp(t, "llU") || (cmp(t, "zu") ||
			cmp(t, "zU")))
		return (ft_print_u(node, ft_itoa_ull(va_arg(args, unsigned long)), 0));
	else if (cmp(t, "f") || cmp(t, "lf") || cmp(t, "F") || cmp(t, "lF"))
		return (ft_print_float(node, va_arg(args, double), 0));
	else if (cmp(t, "Lf") || cmp(t, "LF"))
		return (ft_print_ld(node, va_arg(args, long double), 0));
	else if (ft_strchr(t, 'x') || ft_strchr(t, 'X'))
		return (ft_ntoa_dispatcher(node, va_arg(args, char*), 16));
	else if (cmp(t, "p") || cmp(t, "lp"))
		return (ft_ntoa_dispatcher(node, va_arg(args, char*), 16));
	else
		return (ft_print_dispatcher3(node, t, args));
	return (0);
}

int			ft_print_dispatcher(t_type *node, va_list args)
{
	char	*t;
	int		len;

	len = 0;
	t = node->type;
	if (cmp(t, "s"))
		return (ft_print_string(node, va_arg(args, char *), 0));
	else if (cmp(t, "c"))
		return (ft_print_char(node, va_arg(args, int), 0));
	else if (cmp(t, "C") || cmp(t, "lc"))
		return (ft_print_char(node, (wchar_t)va_arg(args, int), 0));
	else if (cmp(t, "d") || cmp(t, "i"))
		return (ft_print_int(node, ft_itoa(va_arg(args, int)), 0));
	else if (cmp(t, "hd") || cmp(t, "hi"))
		return (ft_print_int(node, ft_itoa((short)va_arg(args, int)), 0));
	else if (cmp(t, "hhd") || cmp(t, "hhi"))
		return (ft_print_int(node, ft_itoa((char)va_arg(args, int)), 0));
	else if (cmp(t, "ld") || cmp(t, "lld") || cmp(t, "li") || cmp(t, "lli") ||
		cmp(t, "D") || cmp(t, "lD") || cmp(t, "llD") || cmp(t, "hD") ||
		cmp(t, "hhD") || cmp(t, "zd") || cmp(t, "zi"))
		return (ft_print_int(node, ft_itoa_ll(va_arg(args, long)), 0));
	else
		return (ft_print_dispatcher2(node, t, args));
	return (0);
}
