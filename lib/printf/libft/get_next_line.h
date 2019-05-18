/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:44:20 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/03/27 11:30:06 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 128

# if (BUFF_SIZE <= 0)
#  error BUFF_SIZE must be > 0
# endif

typedef struct		s_node
{
	char			*data;
	int				fd;
	struct s_node	*next;
}					t_node;

int					get_next_line(const int fd, char **line);

#endif
