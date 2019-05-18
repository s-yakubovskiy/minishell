/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:41:22 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/18 17:09:29 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL
# define FT_MINISHELL

# include <sys/wait.h>
# include<sys/types.h>

# include "../lib/printf/ft_printf.h"
# include "../lib/printf/libft/get_next_line.h"


# define ISSPACE(x) (x == ' ' || x == '\n')
# define clear() ft_printf("\033[H\033[J")
# define SPLIT_DELIM " \t\r\n\a"
# define BUFF_LN 5



/*
 **			t_env_structure
 **			linked link functions
 */

typedef struct			s_env
{
	int					index;
	char 				key[50];
	char 				path[200];
	struct s_env		*next;
}						t_env;

typedef void (*callback)(t_env *data);

t_env		*create_env(int index, char *key, char *path, t_env* next);
t_env		*prepend_env(t_env *head, char *key, char *path);
t_env		*append_env(t_env *head, char *key, char *path);
t_env		*remove_front_env(t_env* head);
t_env		*remove_back_env(t_env* head);
t_env		*remove_any_env(t_env *head, t_env *nd);
t_env		*search_key(t_env *head, char *key);
void		dispose_env(t_env *head);
int			count_env(t_env *head);
void		display_env(t_env *n);


/*
 **			minishell
 **			core functions
 */

char		**g_env;
char		*read_ln(void);
char		**line_split(char const *s, char *delim);
int			launch_dispatcher(char **args);
int			launch_proc(char **args);
void		*ft_realloc(void *ptr, size_t originalLength, size_t newLength);
char		**environ_grab(void);
char 		*env_path(char *key);

#endif
