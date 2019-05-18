/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:12:20 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 16:01:39 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fl_zero(t_type *node, char *str, int *i, int c)
{
	int		flag_minus;
	int		flag_zero;
	int		flag_mod;

	flag_minus = ft_isfl_in(node, '-');
	flag_zero = ft_isfl_in(node, '0');
	flag_mod = 0;
	if (c == 0)
		flag_mod += 1;
	while (*i < node->width - flag_mod)
	{
		if (flag_minus == FAIL)
			str[*i] = (flag_zero == SUCCESS ? '0' : ' ');
		else
			str[*i] = ' ';
		*i = *i + 1;
	}
}

static void	fl_minus(t_type *node, char *to, char *from, int *i)
{
	int		len;
	int		flag_minus;
	int		j;

	j = 0;
	len = ft_strlen(from);
	flag_minus = ft_isfl_in(node, '-');
	if (flag_minus == FAIL)
		while (len >= 0)
		{
			to[*i] = from[len];
			*i = *i - 1;
			len = len - 1;
		}
	else
		while (from[j] != '\0')
		{
			to[j] = from[j];
			++j;
		}
}

int			ifzerowrite(t_type *node, int i)
{
	char	sp;
	char	zero;
	char	nul;

	sp = 32;
	nul = 0;
	zero = '0';
	while (i < node->width - 1)
	{
		if (ft_isfl_in(node, '0') == 0)
			write(1, &zero, 1);
		else
			write(1, &sp, 1);
		i++;
	}
	write(1, &nul, 1);
	return (i);
}

static int	ft_print_char2(t_type *node, int len, char *str, int c)
{
	char	*str2;
	int		i;

	i = 0;
	str2 = ft_strnew(node->width);
	fl_zero(node, str2, &i, c);
	fl_minus(node, str2, str, &i);
	write(1, str2, ft_strlen(str2));
	len = ft_strlen(str2);
	free(str);
	free(str2);
	return (len);
}

int			ft_print_char(t_type *node, int c, int i)
{
	int		len;
	char	*str;

	str = ft_strnew(2);
	if (c == 0)
		return (ifzero(node, i));
	node->precision == 0 ? node->precision = 1 : 0;
	str[0] = c;
	len = ft_strlen(str);
	while (node->precision <= len && node->precision != -1)
		str[len--] = '\0';
	if (node->width != -1 && node->width >= len + 1)
		return (ft_print_char2(node, len, str, c));
	write(1, str, ft_strlen(str));
	len = ft_strlen(str);
	free(str);
	return (len);
}
