/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:22:49 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:55:57 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_c(char const *s, char c)
{
	int		begin;
	int		end;
	char	*new_arr;

	begin = 0;
	end = ft_strlen(s) - 1;
	if (s)
	{
		while (s[begin] == c)
			++begin;
		while (s[end] == c && end >= 0)
			--end;
		new_arr = ft_strsubi(s, begin, end);
		if (new_arr == NULL)
			return (NULL);
		return (new_arr);
	}
	return (NULL);
}
