#include "minishell.h"

void *ft_realloc(void *ptr, size_t originalLength, size_t newLength)
{
	if (newLength == 0)
	{
		free(ptr);
		return NULL;
	}
	else if (!ptr)
	{
		return malloc(newLength);
	}
	else if (newLength <= originalLength)
	{
		return ptr;
	}
	else
	{
		if ((newLength > originalLength))
		{
			void *ptrNew = malloc(newLength);
			if (ptrNew)
			{
				ft_memcpy(ptrNew, ptr, originalLength);
				free(ptr);
			}
			return ptrNew;
		}
		return (0);
	}
}


char *read_ln(void)
{
	int pos = 0;
	int buffsize = BUFF_LN;
	char *buffer = ft_memalloc(buffsize);
	int c;

	if (!buffer) {
		ft_putendl_fd("minishell: couldn't allocate memory", 2);
		exit(-8);
	}

	while (1) {
		// read char
		c = getchar();
		// EOF and crln to \0
		if (c == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		else if (c == EOF)
		{
			ft_putstr("\nTerminated by user\n");
			exit (-111);
		}
		else
			buffer[pos] = c;
		pos++;
		// Expand buffer
		if (pos >= buffsize) {
			buffsize += BUFF_LN;

			buffer = ft_realloc(buffer, pos, buffsize);
//			buffer = buff_expander(buffer, buffsize);
			if (!buffer) {
				ft_putendl_fd("minishell: couldn't allocate memory", 2);
				exit(-8);
			}
		}
	}
}

char	*ft_strjoiner(char const *s1, char const *s2)
{
	char	*new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_arr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_arr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_arr[i] = s1[i];
		++i;
	}
	new_arr[i++] = '/';
	while (s2[j] != '\0')
	{
		new_arr[i] = s2[j];
		++j;
		++i;
	}
	return (new_arr);
}