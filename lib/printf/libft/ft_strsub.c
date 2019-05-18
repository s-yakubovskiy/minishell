/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:52:40 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/11 17:30:49 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_arr;
	char	*fresh;

	if (s == NULL)
		return (NULL);
	fresh = ft_strnew(len);
	if (fresh == NULL)
		return (NULL);
	new_arr = fresh;
	while (s[start] != '\0' && len-- != 0)
		*(fresh++) = s[start++];
	*fresh = '\0';
	return (new_arr);
}
