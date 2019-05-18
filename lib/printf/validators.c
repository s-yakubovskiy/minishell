/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:40:39 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 16:19:14 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flagsvalidator(char flag)
{
	int			i;
	const char	base[6] = {'#', '0', '-', '+', ' ', '\0'};

	i = 0;
	while (base[i] != '\0')
	{
		if (flag == base[i])
			return (SUCCESS);
		++i;
	}
	return (FAIL);
}

/*
** VALIDATE WIDTH AND PRECISION
*/

int		ft_numvalidator(const char *format, size_t *i)
{
	int		len;

	len = 0;
	while (ft_isdigit(format[*i]) == 1 && format[*i] != '\0')
	{
		++len;
		*i = *i + 1;
	}
	if (len > 0)
		return (len);
	return (FAIL);
}

int		ft_typevalidator(t_type *node, int len, size_t *i)
{
	int			j;
	const char	base[][4] = {"c", "s", "p", "lp", "b", "bs", "C", "lc",
	"u", "hu", "hhu", "lu", "llu", "U", "hU", "hhU", "lU", "llU", "jU", "zU",
	"ju", "zu", "hd", "hi", "d", "i", "ld", "li", "lld", "lli", "hhd", "hhi",
	"D", "hD", "hhD", "lD", "llD", "jd", "ji", "o", "O", "ho", "hO", "hho",
	"hhO", "lo", "llo", "lO", "llO", "x", "X", "hx", "hX", "hhx", "hhX", "lx",
	"llx", "lX", "llX", "jo", "jO", "zO", "zo", "zX", "zx", "jx", "jX", "zd",
	"zi", "jD", "zD", "f", "lf", "Lf", "F", "lF", "LF", "%", "clr", ""};

	while (len >= 1)
	{
		j = 0;
		while (ft_strcmp(base[j], "") != 0)
		{
			if (ft_strcmp(node->type, base[j]) == 0)
				return (SUCCESS);
			++j;
		}
		node->type[len - 1] = '\0';
		--len;
		*i = *i - 1;
	}
	return (FAIL);
}
