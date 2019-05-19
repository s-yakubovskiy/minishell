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

t_env*	create_env(int index, char *env, t_env *next)
{
	t_env	*new_env;

	new_env = (t_env*)malloc(sizeof(t_env));
//	printf("%s", env);
	if(new_env == NULL)
	{
		printf("Error creating a new t_env.\n");
		exit(0);
	}
	new_env->index = index;
	strcpy_n2(new_env->path, env, '=');
	strcpy_n(new_env->key, env, '=');
//	ft_strcpy(new_env->key, key);
	new_env->next = next;
	return (new_env);
}

t_env	*prepend_env(t_env *head, char *key, char *path)
{
//	t_env	*new_env;
//
//	if (!(head))
//		head->index = 0;
//	new_env = create_env(head->index + 1, key, path, head);
//	head = new_env;
	return (head);
}

t_env	*append_env(t_env *head, char *env)
{
	t_env	*new_node;

	if (head == NULL)
	{
		g_env = create_env(0, env, NULL);
		return (g_env);
	}
	/* go to the last t_env */
	t_env	*ptr;
	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;

	/* create a new t_env */
	new_node =  create_env(ptr->index + 1, env, NULL);
	ptr->next = new_node;

	return (head);
}

t_env	*remove_front_env(t_env* head)
{
	if(head == NULL)
		return NULL;
	t_env *front = head;
	head = head->next;
	front->next = NULL;
	/* is this the last t_env in the list */
	if(front == head)
		head = NULL;
	free(front);
	return head;
}

/*
    remove t_env from the back of the list
*/
t_env	*remove_back_env(t_env* head)
{
	if(head == NULL)
		return NULL;

	t_env *ptr = head;
	t_env *back = NULL;
	while(ptr->next != NULL)
	{
		back = ptr;
		ptr = ptr->next;
	}

	if(back != NULL)
		back->next = NULL;

	/* if this is the last t_env in the list*/
	if(ptr == head)
		head = NULL;

	free(ptr);
	return head;
}


t_env	*remove_any_env(t_env *head, t_env *nd)
{
	if(nd == NULL)
		return NULL;
	/* if the t_env is the first t_env */
	if(nd == head)
		return remove_front_env(head);

	/* if the t_env is the last t_env */
	if(nd->next == NULL)
		return remove_back_env(head);

	/* if the t_env is in the middle */
	t_env* ptr = head;
	while(ptr != NULL)
	{
		if(ptr->next == nd)
			break;
		ptr = ptr->next;
	}
	if(ptr != NULL)
	{
		t_env* tmp = ptr->next;
		ptr->next = tmp->next;
		tmp->next = NULL;
		free(tmp);
	}
	return head;
}

t_env	*search_key(t_env *head, char *key)
{
	t_env	*ptr;

	ptr = head;
	while(ptr != NULL)
	{
		if(ft_strcmp(ptr->key, key) == 0)
			return ptr;
		ptr = ptr->next;
	}
	return (NULL);
}

void	dispose_env(t_env *head)
{
	t_env	*ptr;
	t_env	*tmp;

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

int		count_env(t_env *head)
{
	t_env *ptr = head;
	int c = 0;
	while(ptr != NULL)
	{
		c++;
		ptr = ptr->next;
	}
	return (c);
}

void	display_env(t_env *n)
{
	if(n != NULL)
		printf("%s=%s\n", n->key, n->path);
}

void	grab_vault(t_env *n)
{
	if(n != NULL)
	{

		strcpy_n3(vault->arr[vault->index], n->key, n->path);
		vault->index += 1;
//		printf("%s=%s\n", n->key, n->path);
	}
}

void	traverse(t_env *head, callback f)
{
	t_env	*ptr;

	ptr = head;
	while(ptr != NULL)
	{
		f(ptr);
		ptr = ptr->next;
	}
}