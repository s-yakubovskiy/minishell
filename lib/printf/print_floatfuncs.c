/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floatfuncs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 09:33:38 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 13:52:34 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_zerofiller2(t_type *node, char *str, int len, int *i)
{
	while (*i < len)
	{
		if (ft_isfl_in(node, '0') == 0)
			str[*i] = (ft_isfl_in(node, '-') == 0 &&
				(node->width < node->precision ||
					node->precision == -1)) ? ' ' : ' ';
		else
			str[*i] = ' ';
		*i = *i + 1;
	}
}

void	ft_zerofiller3(t_type *node, char *str, int len, int i)
{
	int		sp;

	sp = ft_isfl_in(node, ' ') == -1;
	if (ft_isfl_in(node, '0') == 0 && ft_isfl_in(node, '-') == -1)
	{
		while (i < len)
		{
			str[i] = '0';
			i++;
		}
		if (sp == 0)
			str[0] = ' ';
	}
}

int		ft_isnegative2(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
		if (str[i++] == '-')
		{
			flag = 1;
			break ;
		}
	i = 0;
	if (flag == 1)
		return (SUCCESS);
	return (FAIL);
}

void	ft_flagminus_num2(char *str, int len)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		len -= (str[ft_strlen(str) - 1] == ' ') ? 1 : 0;
		while (len > 0)
		{
			ft_swap(&str[len], &str[len - 1]);
			--len;
		}
		str[len] = '-';
	}
	else
	{
		while (str[i] == ' ' && str[i] != '0' && str[i] != '\0')
			i++;
		str[i - 1] = '-';
	}
}

int		is_const(char *str)
{
	const char	base[][5] = { "inf", "-inf", "nan", "" };
	int			i;

	i = 0;
	while (ft_strcmp(base[i], "") != 0)
	{
		if (ft_strcmp(base[i], str) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}
