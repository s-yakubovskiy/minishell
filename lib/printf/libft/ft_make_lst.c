/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:29:47 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/06 14:01:55 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_make_lst(t_list **head, size_t len)
{
	t_list	*ptr;

	if (*head == NULL)
		*head = (t_list*)malloc(sizeof(head));
	ptr = *head;
	while (len-- > 0)
	{
		ptr->next = (t_list*)malloc(sizeof(ptr));
		ptr = ptr->next;
	}
}
