/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:15:57 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/09 14:23:45 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_w_count_c_ext(const char *s, char *delim, int nw, int i)
{
	while (s[i] != '\0')
	{
		if (strchr(delim, s[i]))
		{
			while (strchr(delim, s[i]))
			{
				i++;
				if (s[i] == '\0')
				{
					nw++;
					return (nw);
				}
			}
			++nw;
		}
		i++;
	}
	nw++;
	return (nw);
}

static int	ft_w_count_c(const char *s, char *delim)
{
	int		nw;
	int		i;

	nw = 0;
	i = 0;
	while (strchr(delim, s[i]))
	{
		i++;
		if (s[i] == '\0')
			return (nw);
	}
	return (ft_w_count_c_ext(s, delim, nw, i));
}

static void	ft_split_free(char **n_arr, int len)
{
	while (len >= 0)
	{
		ft_memdel((void **)&n_arr[len]);
		--len;
	}
	ft_memdel((void **)&n_arr[len]);
	ft_memdel((void **)&n_arr);
}

static void	ft_distributor(char *t_arr, char **n_arr, char *delim, int w_c)
{
	int		i;
	int		j;
	int		len;
	int     x;

	i = -1;
	x = 0;
	while (t_arr[++i] != '\0')
	{
		j = i;
		len = 0;
		while (!ft_strchr(delim, t_arr[i]) && t_arr[i] != '\0')
		{
			++i;
			++len;
		}
		if (len > 0 && x < w_c)
		{
			if ((n_arr[x] = ft_strnew(len)) == NULL)
			{
				ft_split_free(n_arr, x);
				return ;
			}
			ft_strncpy(n_arr[(x++)], t_arr + j, len);
		}
	}
}

char		**line_split(char const *s, char *delim)
{
	char	**new_arr;
	int		w_amount;

	if (s == NULL)
		return (NULL);
	w_amount = ft_w_count_c(s, delim);
	new_arr = (char **)ft_memalloc(sizeof(char *) * w_amount + 10);
	if (new_arr == NULL)
		return (NULL);
	new_arr[w_amount + 1] = 0;
	ft_distributor((char*)s, new_arr, delim, w_amount);
	return (new_arr);
}
