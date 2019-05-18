/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 08:34:03 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:51:59 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_arr;

	i = -1;
	new_arr = (unsigned char *)s;
	while (++i < n)
	{
		if (*new_arr == (unsigned char)c)
			return (new_arr);
		++new_arr;
	}
	return (NULL);
}
