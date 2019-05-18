/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:47:44 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:54:21 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_arr;
	char			*begining;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = -1;
	if ((new_arr = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	begining = new_arr;
	while (s[++i] != '\0')
		*new_arr++ = (f)(i, s[i]);
	*new_arr = '\0';
	return (begining);
}
