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
		if (c == EOF || c == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
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