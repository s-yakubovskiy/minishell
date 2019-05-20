/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:18:59 by agottlie          #+#    #+#             */
/*   Updated: 2019/05/20 15:39:53 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_w_count_c(const char *s, char c)
{
	int		state;
	int		nw;
	int		i;

	state = 0;
	nw = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			++nw;
		}
	}
	return (nw);
}

static void	ft_split_free(char **n_arr, int len)
{
	while (len >= 0)
	{
		free(n_arr[len]);
		--len;
	}
}

static void	ft_distributor(char *t_arr, char **n_arr, char c, int w_c)
{
	int		i;
	int		j;
	int		g;
	int		len;

	i = -1;
	j = 0;
	g = 0;
	len = 0;
	while (t_arr[++i] != '\0')
	{
		j = i--;
		len = 0;
		while (t_arr[++i] != c && t_arr[i] != '\0')
			++len;
		if (len > 0 && g < w_c)
		{
			if ((n_arr[g] = ft_strnew(len)) == NULL)
			{
				ft_split_free(n_arr, g);
				return ;
			}
			ft_strncpy(n_arr[g++], t_arr + j, len);
		}
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**new_arr;
	int		w_amount;

	if (s == NULL)
		return (NULL);
	w_amount = ft_w_count_c(s, c);
	new_arr = (char **)malloc(sizeof(char *) * w_amount + 1);
	if (new_arr == NULL)
		return (NULL);
	new_arr[w_amount] = 0;
	ft_distributor((char*)s, new_arr, c, w_amount);
	return (new_arr);
}
