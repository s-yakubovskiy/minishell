/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colorize_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 09:47:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 15:10:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putchar_cyan(void)
{
	write(1, "\e[36;1m", 8);
}

static void	putchar_magenta(void)
{
	write(1, "\e[31;1m", 8);
}

static void	putchar_yellow(void)
{
	write(1, "\e[33;1m", 8);
}

static void	reset_attr(void)
{
	write(1, "\x1b[0m", 5);
}

void		colorize_str(char *str, int mod)
{
	int	i;

	i = 0;
	mod > 7 ? mod = 0 : 0;
	while (*str)
	{
		if (mod == 0)
		{
			i >= 3 ? i = 0 : i;
			i == 0 ? putchar_cyan() : i;
			i == 2 ? putchar_yellow() : i;
			i == 1 ? putchar_magenta() : i;
		}
		mod == 1 ? putchar_cyan() : 0;
		mod == 2 ? putchar_magenta() : 0;
		mod == 3 ? putchar_yellow() : 0;
		mod == 4 ? write(1, "\e[32;1m", 8) : 0;
		mod == 5 ? write(1, "\e[34;1m", 8) : 0;
		mod == 6 ? write(1, "\e[35;1m", 8) : 0;
		mod == 6 ? write(1, "\e[45;1m", 8) : 0;
		ft_putchar(*str);
		str++;
		i++;
	}
	reset_attr();
}
