/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:41:22 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 13:45:31 by yharwyn-         ###   ########.fr       */
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
# define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
# define SPLIT_DELIM " \t\r\n\a\""
# define BUFF_LN 5
# define IS_QUOTE(x) (x == '"' || x == '\'')


/*
 **			t_env_structure
 **			linked link functions
 */



typedef struct			s_vault
{
	int					index;
	char 				key[50];
	char 				path[200];
	struct s_vault		*next;
}						t_vault;

typedef struct			s_env
{
	int					index;
	char 				**c_env;
	struct s_vault		*vault;
	void 				(*updateEnv)();
	void				(*printEnv)();
	void				(*getDir)();
}						t_env;

typedef void (*callback)(t_vault *data);

t_vault		*create_env(int index, char *env, t_vault* next);
t_vault		*prepend_env(t_vault *head, char *key, char *path);
t_vault		*append_env(t_vault *head, char *env);
t_vault		*remove_front_env(t_vault* head);
t_vault		*remove_back_env(t_vault* head);
t_vault		*remove_any_env(t_vault *head, t_vault *nd);
t_vault		*search_key(t_vault *head, char *key);
void		dispose_env(t_vault *head);
int			count_env(t_vault *head);
void		display_env(t_vault *n);
void		traverse(t_vault *head, callback f);
void		grab_vault(t_vault *n);
void		update_env(void);


/*
 **			minishell
 **			core functions
 */

t_env		*g_env;
char		*read_ln(void);
char		**line_split(char const *s, char *delim);
int			launch_dispatcher(char **args);
int			launch_proc(char **args);
void		*ft_realloc(void *ptr, size_t originalLength, size_t newLength);
t_vault		*environ_grab(t_vault *root);
char 		*env_path(char *key);
char		*ft_strjoiner(char const *s1, char const *s2);

void		proc_signal_handler(int signo);
void		signal_handler(int signo);
void		get_cwd(char *str);
void		string_var_parser(char **line);

#endif
