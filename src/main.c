/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:41:11 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 21:41:11 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		shell_init(void)
{
	char	*username;

	username = getenv("USER");
	CLEAR();
	ft_printf("\n\n\n\n******************"
	"****************************");
	ft_printf("\n\n\n\t*******MINISHELL PROJECT*******");
	ft_printf("\n\n\t-school 21 unix branch project-");
	ft_printf("\n\t-use   at  your  own  risk  :D-");
	ft_printf("\n\n\n\n*******************"
	"***************************");
	ft_printf("\n\n\nUSER is: @%s", username);
	ft_printf("\n");
	sleep(1);
	CLEAR();
}

static void	free_args(char **args)
{
	int i;

	i = 0;
	while (args[i] != 0)
	{
		ft_memdel((void **)&args[i]);
		i++;
	}
	ft_memdel((void**)&args);
}

void		shell_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	shell_init();
	status = 1;
	while (status)
	{
		signal(SIGINT, signal_handler);
		ft_printf("$> ");
		line = read_ln();
		args = line_split(line, SPLIT_DELIM);
		status = launch_dispatcher(args);
		free(line);
		free_args(args);
	}
}

void		env_init(t_vault *ptr)
{
	g_env = ft_memalloc(sizeof(t_env));
	g_env->c_env = ft_memalloc(300);
	g_env->index = 0;
	g_env->vault = ptr;
	g_env->update_envv = update_env;
	g_env->print_envv = traverse;
	g_env->get_dir = get_cwd;
	g_env->get_dir(search_key(g_env->vault, "PWD")->path);
	g_env->get_dir(search_key(g_env->vault, "OLDPWD")->path);
	g_env->builtin_func[0] = &cd_shell;
	g_env->builtin_func[1] = &help_shell;
	g_env->builtin_func[2] = &exit_shell;
	g_env->builtin_func[3] = &set_env;
	g_env->builtin_func[4] = &set_env;
	g_env->builtin_func[5] = &unset_env;
	g_env->builtin_func[6] = &echo;
	g_env->i = 0;
	ft_strcpy(g_env->builtin_str[0], "cd");
	ft_strcpy(g_env->builtin_str[1], "help");
	ft_strcpy(g_env->builtin_str[2], "exit");
	ft_strcpy(g_env->builtin_str[3], "env");
	ft_strcpy(g_env->builtin_str[4], "setenv");
	ft_strcpy(g_env->builtin_str[5], "unsetenv");
	ft_strcpy(g_env->builtin_str[6], "echo");
}

int			main(void)
{
	t_vault *ptr;

	ptr = NULL;
	ptr = environ_grab(ptr);
	env_init(ptr);
	traverse(g_env->vault, grab_vault);
	shell_loop();
	clean_up();
	dispose_env(g_env->vault);
	dispose_env(ptr);
	return (0);
}
