/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:41:11 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/05 19:40:17 by yharwyn-         ###   ########.fr       */
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

void sigint_handler(int signal)
{
	printf("\n");
}

void mysh_update_cwd_info(void)
{
	getcwd(shell->cur_dir, sizeof(shell->cur_dir));
}

void sh_init()
{
	struct sigaction	sigint_action;
	pid_t				pid;
	struct passwd		*pw;
	int					i;
	extern char 		**environ;

	sigint_action.sa_flags = 0;
	i = -1;
	sigint_action.sa_handler = &sigint_handler;
	sigemptyset(&sigint_action.sa_mask);
	sigaction(SIGINT, &sigint_action, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	pid = getpid();
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	shell = (shell_info*)malloc(sizeof(shell_info));
	shell->env = environ;
	getlogin_r(shell->cur_user, sizeof(shell->cur_user));
	pw = getpwuid(getuid());
	strcpy(shell->pw_dir, pw->pw_dir);
	while (++i < NR_JOBS)
		shell->jobs[i] = NULL;
	mysh_update_cwd_info();
}

void mysh_print_promt(void)
{
//	printf(COLOR_CYAN "%s" COLOR_NONE " in " COLOR_YELLOW "%s" COLOR_NONE "\n", shell->cur_user, shell->cur_dir);
	printf(COLOR_CYAN "21sh>" COLOR_NONE " ");
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

void		shell_loop()
{
	char		*line;
	char		**args;
	job			*job;
	int			status;

//	shell_init();
	sh_init();
	status = 1;
	while (status >= 0)
	{
		signal(SIGINT, signal_handler);
		mysh_print_promt();
		line = read_ln();
		if (strlen(line) == 0)
		{
			check_zombie();
			continue ;
		}
		job = shell_parse_command(line);
		args = line_split(line, SPLIT_DELIM);
//		status = launch_dispatcher(args);
		status = shell_launch_job(job);
//		free(line);
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

int			main(int argc, char **argv, char **env)
{
	t_vault *ptr;

	ptr = NULL;
	ptr = environ_grab(ptr);
	const char* s = getenv("PATH");
	env_init(ptr);
	traverse(g_env->vault, grab_vault);
	shell_loop();

//	clean_up();
//	dispose_env(g_env->vault);
//	dispose_env(ptr);
	return (0);
}
