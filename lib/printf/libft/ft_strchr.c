/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:11:42 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/12 15:54:49 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*new_arr;

	new_arr = (char*)s;
	while (*new_arr != '\0')
	{
		if (*new_arr == c)
			return (new_arr);
		++new_arr;
	}
	if (c == '\0')
		return (new_arr);
	return (NULL);
}
