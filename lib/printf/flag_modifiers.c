/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_modifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 09:32:22 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/18 13:04:31 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fillin_num2(int str_len, char *to, char *from, int len)
{
	while (str_len >= 0)
	{
		to[len - 1] = from[str_len];
		--len;
		--str_len;
	}
}

void		ft_fillin_num(t_type *node, char *to, char *from, int len)
{
	int		i;
	int		str_len;
	int		pr_copy;
	int		inf;

	i = 0;
	str_len = ft_strlen(from) - 1;
	pr_copy = node->precision - 1;
	inf = ft_strcmp(from, "-inf") == 0 || ft_strcmp(from, "inf") == 0;
	if (ft_isfl_in(node, '-') == SUCCESS)
	{
		turnoff_fl(node->flags, '0');
		while (str_len >= 0)
		{
			if (pr_copy > str_len && inf != 1)
				to[pr_copy] = from[str_len];
			else
				to[i] = from[i];
			++i;
			--str_len;
			--pr_copy;
		}
	}
	else
		ft_fillin_num2(str_len, to, from, len);
}

void		ft_zerofiller(t_type *node, char *str, int len, int *i)
{
	int		pr_copy;

	pr_copy = node->precision;
	if (ft_isfl_in(node, '-') == SUCCESS)
		while (*i < node->precision)
		{
			str[*i] = '0';
			*i = *i + 1;
		}
	else
		while (pr_copy > 0)
		{
			str[len - 1] = '0';
			--len;
			--pr_copy;
		}
	while (*i < len)
	{
		if ((ft_isfl_in(node, '0') == SUCCESS))
			str[*i] = ((ft_isfl_in(node, '-') == -1 && (node->width
				< node->precision || node->precision == -1))) ? '0' : ' ';
		else
			str[*i] = ' ';
		*i = *i + 1;
	}
}

int			ft_isnegative(char *str)
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
	{
		while (str[i + 1] != '\0')
		{
			ft_swap(&str[i], &str[i + 1]);
			++i;
		}
		str[i] = '\0';
		return (SUCCESS);
	}
	return (FAIL);
}

void		ft_flagsp_num(char *str, int len)
{
	int		i;

	i = 0;
	while (len > 0)
	{
		ft_swap(&str[len], &str[len - 1]);
		--len;
	}
	str[0] = ' ';
}
