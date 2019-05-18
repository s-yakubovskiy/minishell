/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_cases_xop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:56:04 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/17 16:39:37 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			zero_modificators(t_type *node)
{
	if ((node->precision == 0 || node->precision == 1) &&
		ft_strchr(node->flags, '#') && (ft_strchr(node->type, 'o') ||
		ft_strchr(node->type, 'O')))
	{
		node->precision = 0;
		ft_addflag(node, '^');
	}
	else if (ft_strchr(node->type, 'o') || ft_strchr(node->type, 'O') ||
		ft_strchr(node->type, 'x') || ft_strchr(node->type, 'X'))
	{
		ft_addflag(node, '@');
	}
}

static char			*zero_cases_ext(t_type *node, char *str)
{
	if (node->precision == 0 && node->width > 1)
	{
		str = ft_strnew(node->width);
		ft_memset(str, ' ', node->width);
		if ((ft_strchr(node->type, 'o') || ft_strchr(node->type, 'O')) &&
			ft_strchr(node->flags, '#'))
		{
			if (ft_strchr(node->flags, '-'))
				str[0] = '0';
			else
				str[node->width - 1] = '0';
			turnoff_fl(node->flags, '#');
		}
		return (str);
	}
	else
		zero_modificators(node);
	return (0);
}

static char			*zero_cases_p(t_type *node, char *str)
{
	if (node->precision == 0)
	{
		str = ft_strdup("0x");
		return (str);
	}
	else
		add_flag(&node, '#');
	return (str);
}

char				*zero_cases(t_type *node, char *str)
{
	turnoff_fl(node->flags, '#');
	node->width == -1 && node->precision == 0 ? ft_addflag(node, '@') : 0;
	if (node->width == 1 && node->precision == 0 && ft_strchr(node->flags, '#'))
	{
		if (ft_strchr(node->type, 'x') || ft_strchr(node->type, 'X'))
			str = ft_strdup(" ");
		else
			ft_addflag(node, '@');
		turnoff_fl(node->flags, '#');
		return (str);
	}
	if (!((ft_strchr(node->type, 'o') || ft_strchr(node->type, 'O'))
		&& ft_strchr(node->flags, '#')))
		turnoff_fl(node->flags, '#');
	if (ft_strchr(node->type, 'p'))
		return (zero_cases_p(node, str));
	if ((str = zero_cases_ext(node, str)))
		return (str);
	return (0);
}

int					printf_len_corrector(t_type *node, char *str, int len)
{
	len = ft_strlen(str);
	ft_strchr(node->type, '@') && node->width == -1 && node->precision == 0 &&
	!ft_strchr(node->type, 'o') && !ft_strchr(node->type, 'O') ? len-- : 0;
	ft_strchr(node->type, '@') && node->width == 1 && node->precision == 0 &&
	(ft_strchr(node->type, 'o') || ft_strchr(node->type, 'O'))
	? ft_putstr("0") : 0;
	ft_strchr(node->type, '@') && node->width == -1 && node->precision == 0 &&
	ft_strchr(node->type, 'p') ? len++ : 0;
	ft_strchr(node->type, '@') && !ft_strchr(node->type, '^')
	&& node->width == -1 && node->precision == 0 && (ft_strchr(node->type, 'o')
		|| ft_strchr(node->type, 'O')) ? len-- : 0;
	if (cmp(node->type, "p@") && node->width == 1 && node->precision == 0)
	{
		ft_putstr("0x");
		len++;
	}
	return (len);
}
