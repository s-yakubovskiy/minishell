/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 08:33:23 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:55:50 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		begin;
	int		end;
	char	*new_arr;

	if (s == NULL)
		return (NULL);
	begin = 0;
	end = ft_strlen(s) - 1;
	while (s[begin] == ' ' || s[begin] == '\n' || s[begin] == '\t')
		++begin;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t') && end >= 0)
		--end;
	new_arr = ft_strsubi(s, begin, end);
	if (new_arr == NULL)
		return (NULL);
	return (new_arr);
}
