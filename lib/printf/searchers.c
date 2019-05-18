/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 10:30:23 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/14 12:42:38 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_isfl_in(t_type *node, char flag)
{
	int		i;

	i = 0;
	while (node->flags[i] != '\0')
	{
		if (node->flags[i] == flag)
			return (SUCCESS);
		++i;
	}
	return (FAIL);
}

int		ft_flagssearcher(t_type *node, const char *format, size_t *i)
{
	int		j;

	j = 0;
	node->flags = ft_strnew(5);
	while (format[*i] != '\0')
	{
		if (ft_flagsvalidator(format[*i]) == SUCCESS)
		{
			if (ft_isfl_in(node, format[*i]) == FAIL)
			{
				node->flags[j] = format[*i];
				++j;
			}
		}
		else
			return (FAIL);
		*i = *i + 1;
	}
	return (SUCCESS);
}

int		ft_widthsearcher(t_type *node, const char *format, size_t *i)
{
	int		j;
	int		len;
	char	*number;

	j = 0;
	if ((len = ft_numvalidator(format, i)) > 0)
	{
		number = ft_strsubi(format, *i - len, *i - 1);
		node->width = ft_atoi(number);
		free(number);
		return (SUCCESS);
	}
	node->width = -1;
	return (FAIL);
}

int		ft_precisionsearcher(t_type *node, const char *format, size_t *i)
{
	int		j;
	int		len;
	char	*number;

	j = 0;
	while (format[*i] == '.' && format[*i] != '\0')
	{
		*i = *i + 1;
		if (ft_isdigit(format[*i]) == 0 && format[*i] != '.')
		{
			node->precision = 0;
			return (SUCCESS);
		}
		if ((len = ft_numvalidator(format, i)) > 0)
		{
			number = ft_strsubi(format, *i - len, *i - 1);
			node->precision = ft_atoi(number);
			free(number);
			return (SUCCESS);
		}
	}
	node->precision = -1;
	return (FAIL);
}

int		ft_typesearcher(t_type *node, const char *format, size_t *i)
{
	size_t	len;

	len = 0;
	while (len < 3 && format[*i] != '\0')
	{
		++len;
		*i = *i + 1;
	}
	if (len > 0)
	{
		node->type = ft_strsubi(format, *i - len, *i - 1);
		ISFAILED(ft_typevalidator(node, len, i));
		return (SUCCESS);
	}
	else
		node->type = ft_strnew(1);
	return (FAIL);
}
