/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:17:15 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:51:51 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*new_arr;

	if (size > 4294967295)
		return (NULL);
	new_arr = (char *)malloc(sizeof(char) * (size + 1));
	if (new_arr == NULL)
		return (NULL);
	ft_bzero(new_arr, size);
	return (new_arr);
}
