#include "minishell.h"

t_env*	create_env(int index, char *key, char *path, t_env* next)
{
	t_env	*new_env;

	new_env = (t_env*)malloc(sizeof(t_env));
	if(new_env == NULL)
	{
		printf("Error creating a new t_env.\n");
		exit(0);
	}
	new_env->index = index;
	ft_strcpy(new_env->path, path);
	ft_strcpy(new_env->key, key);
	new_env->next = next;

	return (new_env);
}

t_env	*prepend_env(t_env *head, char *key, char *path)
{
	t_env	*new_env;

	if (!(head))
		head->index = 0;
	new_env = create_env(head->index + 1, key, path, head);
	head = new_env;
	return (head);
}

t_env	*append_env(t_env *head, char *key, char *path)
{
	t_env	*new_node;

	if(head == NULL)
		return NULL;
	/* go to the last t_env */
	t_env	*cursor;
	cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;

	/* create a new t_env */
	new_node =  create_env(cursor->index + 1, key, path, NULL);
	cursor->next = new_node;

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

	t_env *cursor = head;
	t_env *back = NULL;
	while(cursor->next != NULL)
	{
		back = cursor;
		cursor = cursor->next;
	}

	if(back != NULL)
		back->next = NULL;

	/* if this is the last t_env in the list*/
	if(cursor == head)
		head = NULL;

	free(cursor);
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
	t_env* cursor = head;
	while(cursor != NULL)
	{
		if(cursor->next == nd)
			break;
		cursor = cursor->next;
	}

	if(cursor != NULL)
	{
		t_env* tmp = cursor->next;
		cursor->next = tmp->next;
		tmp->next = NULL;
		free(tmp);
	}
	return head;

}

t_env	*search_key(t_env *head, char *key)
{
	t_env	*cursor;

	cursor = head;
	while(cursor != NULL)
	{
		if(ft_strcmp(cursor->key, key) == 0)
			return cursor;
		cursor = cursor->next;
	}
	return (NULL);
}

void	dispose_env(t_env *head)
{
	t_env	*cursor;
	t_env	*tmp;

	if(head != NULL)
	{
		cursor = head->next;
		head->next = NULL;
		while(cursor != NULL)
		{
			tmp = cursor->next;
			free(cursor);
			cursor = tmp;
		}
	}
}

int		count_env(t_env *head)
{
	t_env *cursor = head;
	int c = 0;
	while(cursor != NULL)
	{
		c++;
		cursor = cursor->next;
	}
	return (c);
}

void	display_env(t_env *n)
{
	if(n != NULL)
		printf("%s=%s", n->key, n->path);
}