/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:47:27 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:52:10 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*new_arr;
	unsigned char	*old_arr;

	i = -1;
	new_arr = (unsigned char *)dst;
	old_arr = (unsigned char *)src;
	while (++i < n)
		new_arr[i] = old_arr[i];
	return (new_arr);
}
