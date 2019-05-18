/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:32:55 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/12 17:35:51 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new_arr;

	new_arr = (char *)malloc(sizeof(char) * (size + 1));
	if (new_arr == NULL)
		return (NULL);
	ft_bzero(new_arr, size);
	new_arr[size] = '\0';
	return (new_arr);
}
