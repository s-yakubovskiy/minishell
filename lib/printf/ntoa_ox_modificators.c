/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntoa_ox_modificators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 11:28:32 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 16:33:41 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ntoa_xflags(t_type *node, char *n, int base)
{
	if (cmp(node->type, "x") || cmp(node->type, "X"))
		return (ft_ntoa_base((unsigned int)n, base));
	else if (cmp(node->type, "lx") || cmp(node->type, "lX"))
		return (ft_ntoa_base((unsigned long int)n, base));
	else if (ft_strchr(node->type, 'z'))
		return (ft_ntoa_base((size_t)n, base));
	else if (ft_strchr(node->type, 'j'))
		return (ft_ntoa_base((uintmax_t)n, base));
	else if (!ft_strchr(node->type, 'h'))
		return (ft_ntoa_base((unsigned long int)n, base));
	else
	{
		if (cmp(node->type, "hx") || cmp(node->type, "hX"))
			return (ft_ntoa_base((unsigned short)n, base));
		else
			return (ft_ntoa_base((unsigned char)n, base));
	}
}

static char		*ntoa_oflags_ext(t_type *node, char *n, int base)
{
	if (cmp(node->type, "ho") || cmp(node->type, "ho$"))
		return (ft_ntoa_base((unsigned short)n, base));
	else if (cmp(node->type, "hO") || cmp(node->type, "hhO") ||
		cmp(node->type, "hO$") || cmp(node->type, "hhO$"))
		return (ft_ntoa_base((unsigned long)n, base));
	else
		return (ft_ntoa_base((unsigned char)n, base));
}

char			*ntoa_oflags(t_type *node, char *n, int base)
{
	if (cmp(node->type, "o") || cmp(node->type, "o$"))
		return (ft_ntoa_base((unsigned int)n, base));
	else if (cmp(node->type, "O"))
		return (ft_ntoa_base((unsigned long)n, base));
	else if (cmp(node->type, "lo") || cmp(node->type, "llo") ||
		cmp(node->type, "lO") || cmp(node->type, "llO"))
		return (ft_ntoa_base((long)n, base));
	else if (ft_strchr(node->type, 'z'))
		return (ft_ntoa_base((size_t)n, base));
	else if (ft_strchr(node->type, 'j'))
		return (ft_ntoa_base((uintmax_t)n, base));
	if (!ft_strchr(node->type, 'h'))
	{
		if ((int)n < 0)
			return (ft_ntoa_base((unsigned long int)n, base));
		else
			return (ft_ntoa_base((int)n, base));
	}
	else
		return (ntoa_oflags_ext(node, n, base));
}

void			add_flag(t_type **node, char mod)
{
	int i;

	i = 0;
	if (!(*node)->flags)
		(*node)->flags = ft_strnew(5);
	while ((*node)->flags[i] != '\0')
		i++;
	(*node)->flags[i] = mod;
	i++;
	(*node)->flags[i] = '\0';
}

void			turnoff_fl(char *flags, char c)
{
	int		i;
	char	buf;

	i = -1;
	while (flags[++i] != '\0')
	{
		if (flags[i] == c)
		{
			if (flags[i + 1] == '\0')
				flags[i] = '\0';
			else
			{
				buf = flags[i];
				flags[i] = flags[i + 1];
				flags[i + 1] = buf;
			}
		}
	}
}
