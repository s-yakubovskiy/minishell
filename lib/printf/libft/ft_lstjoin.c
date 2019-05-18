/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:49:24 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/06 14:02:23 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstjoin(t_list **head, size_t len)
{
	t_list	*ptr;

	if (*head == NULL)
		return ;
	ptr = *head;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ft_make_lst(&ptr, len);
}
