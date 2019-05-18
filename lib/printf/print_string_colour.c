/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string_colour.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:13:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/02/18 15:15:02 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_color_string(t_type *node, char *str, int i, int mod)
{
	int		len;
	char	*str2;

	str = ft_strdup((str == NULL) ? "(null)" : str);
	len = ft_strlen(str);
	if (node->width != -1 && node->width >= len + 1)
	{
		str2 = ft_strnew(node->width);
		ft_flagzero(node, str2, &i);
		ft_flagminus(node, str2, str, &i);
		colorize_str(str2, mod);
		len = ft_strlen(str2);
		free(str2);
		free(str);
		return (len);
	}
	colorize_str(str, mod);
	len = ft_strlen(str);
	free(str);
	return (len);
}
