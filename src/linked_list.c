/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:19:23 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 17:34:29 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vault		*prepend_env(t_vault *head, char *line)
{
	t_vault	*new_env;

	if (head == NULL)
	{
		head = create_env(0, line, NULL);
		return (head);
	}
	new_env = create_env(head->index + 1, line, NULL);
	head = new_env;
	return (head);
}

t_vault		*append_env(t_vault *head, char *line)
{
	t_vault	*new_node;
	t_vault	*ptr;

	if (head == NULL)
	{
		head = create_env(0, line, NULL);
		return (head);
	}
	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	new_node = create_env(ptr->index + 1, line, NULL);
	ptr->next = new_node;
	return (head);
}

t_vault		*remove_front_env(t_vault *head)
{
	t_vault	*front;

	if (head == NULL)
		return (NULL);
	front = head;
	head = head->next;
	front->next = NULL;
	if (front == head)
		head = NULL;
	free(front);
	return (head);
}

t_vault		*remove_back_env(t_vault *head)
{
	t_vault *ptr;
	t_vault *back;

	if (head == NULL)
		return (NULL);
	ptr = head;
	back = NULL;
	while (ptr->next != NULL)
	{
		back = ptr;
		ptr = ptr->next;
	}
	if (back != NULL)
		back->next = NULL;
	if (ptr == head)
		head = NULL;
	free(ptr);
	return (head);
}
