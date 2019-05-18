/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 14:14:27 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/03/27 11:54:13 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_node	*ft_lstnew_light(int fd)
{
	t_node		*root;

	if (!(root = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	(fd >= 0) ? root->fd = fd : 0;
	root->data = NULL;
	root->next = NULL;
	return (root);
}

static void		ft_datamerge_lst(t_node **root, char *data,
	size_t start, size_t finish)
{
	t_node		*ptr;
	size_t		i;
	size_t		size;

	i = 0;
	size = finish - start;
	ptr = (*root);
	ptr->data = ft_strnew(size);
	while (i < (size - 1))
	{
		ptr->data[i] = data[start];
		i++;
		start++;
	}
}

static t_node	*ft_check_fd(t_node **root, int fd)
{
	t_node *ptr;

	if (!(*root))
		return (ft_lstnew_light(fd));
	ptr = *root;
	if (ptr->fd == fd)
		return (ptr);
	else
	{
		while (ptr->next)
		{
			if (ptr->fd == fd)
				return (ptr);
			ptr = ptr->next;
		}
		ptr->next = ft_lstnew_light(fd);
	}
	if (ptr->fd == fd)
		return (ptr);
	return (ptr->next);
}

static int		gnl_workhorse(char **tmp, char *buff, char **line, int fd)
{
	char			*tmp_free;
	int				n;

	while (!ft_strchr((*tmp), '\n'))
	{
		if ((n = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		buff[n] = '\0';
		tmp_free = ft_strjoin((*tmp), buff);
		ft_strdel(&(*tmp));
		(*tmp) = tmp_free;
		if (!n && !ft_strchr((*tmp), '\n'))
		{
			if (!n && (*tmp) != NULL)
			{
				(*line) = ft_strsub((*tmp), 0, ft_strlen((*tmp)));
				if (ft_strlen((*tmp)) < 1)
					return (0);
				ft_strdel(&(*tmp));
				return (1);
			}
			return (0);
		}
	}
	return (8);
}

int				get_next_line(const int fd, char **line)
{
	char			*tmp;
	char			buff[BUFF_SIZE + 1];
	static t_node	*root;
	t_node			*ptr;
	int				n;

	if (root == NULL)
	{
		root = ft_check_fd(&root, fd);
		ptr = root;
	}
	ptr = ft_check_fd(&root, fd);
	tmp = ft_strnew(0);
	if (ptr->data != NULL)
	{
		tmp = ft_strjoin(tmp, ptr->data);
		ft_strdel(&ptr->data);
	}
	if ((n = gnl_workhorse(&tmp, buff, line, fd)) != 8)
		return (n);
	n = ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n'));
	(*line) = ft_strsub(tmp, 0, (n));
	ft_datamerge_lst(&ptr, (tmp + 1), (n), ft_strlen(tmp));
	ft_strdel(&tmp);
	return (1);
}
