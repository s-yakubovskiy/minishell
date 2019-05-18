/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:15:23 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/06 15:19:42 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		g;
	int		len;

	i = ft_strlen(s1) - 1;
	g = -1;
	len = ft_strlen(s1) + ft_strlen(s2) - 1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (++i <= len)
		s1[i] = s2[++g];
	s1[i] = '\0';
	return (s1);
}
