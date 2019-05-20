/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:31:37 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 22:04:39 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_env(t_vault *n)
{
	if (n != NULL)
		ft_printf("%s=%s\n", n->key, n->path);
}

void		traverse(t_vault *head, t_callback f)
{
	t_vault	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		f(ptr);
		ptr = ptr->next;
	}
}

void		clean_up(void)
{
	int i;

	i = 0;
	while (g_env->c_env[i] != 0)
	{
		ft_memdel((void **)&g_env->c_env[i]);
		i++;
	}
	ft_memdel((void **)&g_env->c_env);
	g_env->index = 0;
}

void		update_env(void)
{
	clean_up();
	traverse(g_env->vault, grab_vault);
}
