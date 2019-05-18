/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:04:12 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:53:59 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		g;
	size_t	orig_buf_size;

	g = -1;
	i = ft_strlen(dst) - 1;
	orig_buf_size = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen(src));
	if (size > ft_strlen(dst))
	{
		while (++i < (size - 1))
			dst[i] = src[++g];
		dst[i] = '\0';
		return (orig_buf_size + ft_strlen(src));
	}
	return (size + ft_strlen(src));
}
