/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:33:38 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 21:54:26 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*strcpy_till_n(char *dst, const char *src, char c)
{
	int		i;

	i = -1;
	while (src[++i])
	{
		if (src[i] == c)
		{
			dst[i] = '\0';
			return (dst);
		}
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return (dst);
}

static char	*strcpy_n2(char *dst, const char *src, char c)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (src[++i])
	{
		if (src[i] == c)
			break ;
	}
	if (i > 0)
	{
		while (src[++i])
		{
			dst[j] = src[i];
			j++;
		}
	}
	dst[j] = '\0';
	return (dst);
}

static char	*strcpy_n3(char *dst, const char *src, char *src2)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (src[++i])
	{
		dst[i] = src[i];
	}
	dst[i] = '=';
	while (src2[++j])
	{
		dst[++i] = src2[j];
	}
	dst[++i] = '\0';
	return (dst);
}

t_vault		*create_env(int index, char *line, t_vault *next)
{
	t_vault	*new_env;

	new_env = (t_vault*)malloc(sizeof(t_vault));
	if (new_env == NULL)
	{
		ft_printf("Error creating a new t_vault.\n");
		exit(0);
	}
	new_env->index = index;
	strcpy_n2(new_env->path, line, '=');
	strcpy_till_n(new_env->key, line, '=');
	new_env->next = next;
	return (new_env);
}

void		grab_vault(t_vault *n)
{
	if (n != NULL)
	{
		if (g_env->c_env == NULL)
			g_env->c_env = ft_memalloc(300);
		g_env->c_env[g_env->index] = ft_memalloc(300);
		strcpy_n3(g_env->c_env[g_env->index], n->key, n->path);
		g_env->index += 1;
	}
}
