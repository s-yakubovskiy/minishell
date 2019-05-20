/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:32:32 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 20:41:32 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t original_length, size_t new_length)
{
	void *ptr_new;

	if (new_length == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_length));
	else if (new_length <= original_length)
		return (ptr);
	else
	{
		if ((new_length > original_length))
		{
			ptr_new = malloc(new_length);
			if (ptr_new)
			{
				ft_memcpy(ptr_new, ptr, original_length);
				free(ptr);
			}
			return (ptr_new);
		}
		return (0);
	}
}
