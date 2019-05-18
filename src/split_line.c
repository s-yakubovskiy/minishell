#include "minishell.h"

static int	ft_w_count_c(const char *s, char *delim)
{
	int		state;
	int		nw;
	int		i;

	state = 0;
	nw = 0;
	i = 0;
	while (strchr(delim, s[i]))
	{
		i++;
		if (s[i] == '\0')
			return (nw);
	}
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
//	nw == 0 ? nw += 1 : 0;
	return(nw);
}

static void	ft_split_free(char **n_arr, int len)
{
	while (len >= 0)
	{
		free(n_arr[len]);
		--len;
	}
}

static void	ft_distributor(char *t_arr, char **n_arr, char *delim, int w_c)
{
	int		i;
	int		j;
	int		g;
	int		len;

	i = -1;
	g = 0;
	while (t_arr[++i] != '\0')
	{
		j = i;
		len = 0;
		while (!ft_strchr(delim, t_arr[i]) && t_arr[i] != '\0')
		{
			++i;
			++len;
		}
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

char		**line_split(char const *s, char *delim)
{
	char	**new_arr;
	int		w_amount;

	if (s == NULL)
		return (NULL);
	w_amount = ft_w_count_c(s, delim);
//	printf("%d\n", w_amount);

	new_arr = (char **)ft_memalloc(sizeof(char *) * w_amount + 10);
	if (new_arr == NULL)
		return (NULL);
	new_arr[w_amount + 1] = 0;
	ft_distributor((char*)s, new_arr, delim, w_amount);
	return (new_arr);
}


