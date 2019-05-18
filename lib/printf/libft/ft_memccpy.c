/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:45:18 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:51:55 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	int				k;
	unsigned char	ch;
	unsigned char	*new_arr;
	unsigned char	*old_arr;

	i = -1;
	k = 0;
	ch = (unsigned char)c;
	new_arr = (unsigned char *)dst;
	old_arr = (unsigned char *)src;
	while (++i < n)
		if ((*(new_arr++) = *(old_arr++)) == ch)
			return (new_arr);
	return (NULL);
}
