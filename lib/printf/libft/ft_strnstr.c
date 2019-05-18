/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:09:03 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:55:02 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*src;
	char	*search;
	size_t	g;
	size_t	i;

	src = (char *)haystack;
	search = (char *)needle;
	i = -1;
	g = 0;
	if (ft_strlen(search) == 0)
		return (src);
	while (src[++i] != '\0' && i < len)
		if (src[i] == search[g])
		{
			++g;
			if (search[g] == '\0')
				return (src + (i - g) + 1);
		}
		else
		{
			i = i - g;
			g = 0;
		}
	return (NULL);
}
