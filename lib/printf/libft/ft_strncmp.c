/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:24:03 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:54:29 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*new_arr1;
	unsigned char	*new_arr2;
	size_t			w;

	new_arr1 = (unsigned char *)s1;
	new_arr2 = (unsigned char *)s2;
	w = 0;
	if (n == 0)
		return (0);
	while (*new_arr1 == *new_arr2 && *new_arr1 != '\0' && w < n - 1)
	{
		++new_arr1;
		++new_arr2;
		++w;
	}
	return (*new_arr1 - *new_arr2);
}
