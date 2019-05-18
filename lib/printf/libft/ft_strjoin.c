/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:52:23 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:53:56 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_arr = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (new_arr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_arr[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0')
	{
		new_arr[i] = s2[j];
		++j;
		++i;
	}
	return (new_arr);
}
