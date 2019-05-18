/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:48:41 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:54:24 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	g;

	i = ft_strlen(s1);
	g = 0;
	if (n == 0)
		return (s1);
	while (g < n && s2[g])
	{
		s1[i] = s2[g];
		++i;
		++g;
	}
	s1[i] = '\0';
	return (s1);
}
