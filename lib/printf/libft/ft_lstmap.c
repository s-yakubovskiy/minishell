/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:42:49 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/05 16:51:43 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_new;
	t_list	*new_list;

	if (lst == NULL || *f == NULL)
		return (NULL);
	new_list = (f)(lst);
	begin_new = new_list;
	lst = lst->next;
	while (lst != NULL)
	{
		new_list->next = (f)(lst);
		if (new_list->next == NULL)
			return (NULL);
		lst = lst->next;
		new_list = new_list->next;
	}
	new_list->next = NULL;
	free(lst);
	return (begin_new);
}
