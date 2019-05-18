/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:51:31 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/06 13:53:42 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (*alst == NULL)
		return ;
	tmp = *alst;
	while ((*alst) != NULL)
	{
		tmp = (*alst)->next;
		(del)((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
		(*alst) = tmp;
	}
}
