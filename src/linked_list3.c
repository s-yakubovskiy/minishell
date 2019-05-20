/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:32:14 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 21:29:03 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vault		*remove_any_env(t_vault *head, t_vault *nd)
{
	t_vault	*ptr;
	t_vault	*tmp;

	if (nd == NULL)
		return (NULL);
	if (nd == head)
		return (remove_front_env(head));
	if (nd->next == NULL)
		return (remove_back_env(head));
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->next == nd)
			break ;
		ptr = ptr->next;
	}
	if (ptr != NULL)
	{
		tmp = ptr->next;
		ptr->next = tmp->next;
		tmp->next = NULL;
		free(tmp);
	}
	return (head);
}

t_vault		*search_key(t_vault *head, char *key)
{
	t_vault	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->key, key) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void		dispose_env(t_vault *head)
{
	t_vault	*ptr;
	t_vault	*tmp;

	if (head != NULL)
	{
		ptr = head->next;
		head->next = NULL;
		while (ptr != NULL)
		{
			tmp = ptr->next;
			ft_memdel((void**)(&ptr));
			ptr = tmp;
		}
		ft_memdel((void**)(&ptr));
	}
}

int			count_env(t_vault *head)
{
	t_vault	*ptr;
	int		c;

	ptr = head;
	c = 0;
	while (ptr != NULL)
	{
		c++;
		ptr = ptr->next;
	}
	return (c);
}
