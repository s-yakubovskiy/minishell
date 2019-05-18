/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:04:02 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/17 15:57:35 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_ntoa_base(uintmax_t n, int base)
{
	static char			*nums = "0123456789abcdefghijklmnopqrstuvwxyzABCDEF";
	char				*res;
	unsigned long		len;

	res = NULL;
	len = ft_nlen(n, base);
	if (!(res = (char*)malloc(sizeof(char) * (len + 40))))
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	while (len && n)
	{
		res[len - 1] = nums[ft_abs(n % base)];
		n = n / base;
		len--;
	}
	return (res);
}

static char	*shift_npos_static(char *str, int n, int i, int j)
{
	while (n > 0)
	{
		while (str[i] != ' ')
			i++;
		j = i;
		while (i > 0 && str[i - 1] != ' ')
		{
			ft_swap(&str[i - 1], &str[i]);
			i--;
		}
		n--;
		i++;
	}
	return (str);
}

char		*shift_npos(char *str, int n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[i] == ' ' && str[i + 1] != ' ')
	{
		while (str[i] != '\0')
		{
			if (str[i + 1] == '\0')
				break ;
			ft_swap(&str[i], &str[i + 1]);
			i++;
		}
		str[i] = '\0';
		return (expand_str(str));
	}
	else
		str = shift_npos_static(str, n, i, j);
	return (str);
}

char		*expand_str(char *str)
{
	char	*exp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] == ' ')
		j++;
	j != 1 ? j = 0 : 0;
	exp = ft_strnew(ft_strlen(str) + 2);
	exp[i++] = '0';
	exp[i++] = 'x';
	while (str[j] != '\0')
	{
		exp[i] = str[j];
		j++;
		i++;
	}
	exp[i] = '\0';
	return (exp);
}

double		int2pow(double nb, int pow)
{
	double x;

	x = nb;
	if (pow == 0)
		return (1);
	if (pow < 0)
		return (-1);
	while (--pow)
		nb *= x;
	return (nb);
}
