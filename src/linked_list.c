#include "minishell.h"

static char	*strcpy_n(char *dst, const char *src, char c)
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
	int 	j;

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
	int 	j;

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
	if(new_env == NULL)
	{
		printf("Error creating a new t_vault.\n");
		exit(0);
	}
	new_env->index = index;
	strcpy_n2(new_env->path, line, '=');
	strcpy_n(new_env->key, line, '=');
	new_env->next = next;
	return (new_env);
}

t_vault	*prepend_env(t_vault *head, char *key, char *path)
{
//	t_vault	*new_env;
//
//	if (!(head))
//		head->index = 0;
//	new_env = create_env(head->index + 1, key, path, head);
//	head = new_env;
	return (head);
}

t_vault	*append_env(t_vault *head, char *line)
{
	t_vault	*new_node;

	if (head == NULL)
	{
		head = create_env(0, line, NULL);
		return (head);
	}
	/* go to the last t_vault */
	t_vault	*ptr;
	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;

	/* create a new t_vault */
	new_node =  create_env(ptr->index + 1, line, NULL);
	ptr->next = new_node;

	return (head);
}

t_vault	*remove_front_env(t_vault* head)
{
	if(head == NULL)
		return NULL;
	t_vault *front = head;
	head = head->next;
	front->next = NULL;
	/* is this the last t_vault in the list */
	if(front == head)
		head = NULL;
	free(front);
	return (head);
}

/*
    remove t_vault from the back of the list
*/
t_vault	*remove_back_env(t_vault* head)
{
	if(head == NULL)
		return NULL;

	t_vault *ptr = head;
	t_vault *back = NULL;
	while(ptr->next != NULL)
	{
		back = ptr;
		ptr = ptr->next;
	}

	if(back != NULL)
		back->next = NULL;

	/* if this is the last t_vault in the list*/
	if(ptr == head)
		head = NULL;

	free(ptr);
	return (head);
}


t_vault	*remove_any_env(t_vault *head, t_vault *nd)
{
	if(nd == NULL)
		return NULL;
	/* if the t_vault is the first t_vault */
	if(nd == head)
		return remove_front_env(head);

	/* if the t_vault is the last t_vault */
	if(nd->next == NULL)
		return remove_back_env(head);

	/* if the t_vault is in the middle */
	t_vault* ptr = head;
	while(ptr != NULL)
	{
		if(ptr->next == nd)
			break;
		ptr = ptr->next;
	}
	if(ptr != NULL)
	{
		t_vault* tmp = ptr->next;
		ptr->next = tmp->next;
		tmp->next = NULL;
		free(tmp);
	}
	return (head);
}

t_vault	*search_key(t_vault *head, char *key)
{
	t_vault	*ptr;

	ptr = head;
	while(ptr != NULL)
	{
		if(ft_strcmp(ptr->key, key) == 0)
			return ptr;
		ptr = ptr->next;
	}
	return (NULL);
}

void	dispose_env(t_vault *head)
{
	t_vault	*ptr;
	t_vault	*tmp;

	if(head != NULL)
	{
		ptr = head->next;
		head->next = NULL;
		while(ptr != NULL)
		{
			tmp = ptr->next;
			free(ptr);
			ptr = tmp;
		}
	}
}

int		count_env(t_vault *head)
{
	t_vault *ptr = head;
	int c = 0;
	while(ptr != NULL)
	{
		c++;
		ptr = ptr->next;
	}
	return (c);
}

void	display_env(t_vault *n)
{
	if(n != NULL)
		printf("%s=%s\n", n->key, n->path);
}

void	grab_vault(t_vault *n)
{
	if(n != NULL)
	{
		g_env->c_env[g_env->index] = ft_memalloc(sizeof(char) * 300);
		strcpy_n3(g_env->c_env[g_env->index], n->key, n->path);
		g_env->index += 1;
	}
}

void	traverse(t_vault *head, callback f)
{
	t_vault	*ptr;

	ptr = head;
	while(ptr != NULL)
	{
		f(ptr);
		ptr = ptr->next;
	}
}


static void	clean_up()
{
	while (g_env->index >= 0)
	{
		ft_memdel((void **)&g_env->c_env[g_env->index]);
		g_env->index -= 1;
	}
}
void	update_env()
{
	clean_up();
	traverse(g_env->vault, grab_vault);
//	ft_memdel((void **)&arr);
}