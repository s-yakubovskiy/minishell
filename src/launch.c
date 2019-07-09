/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:16:02 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/09 14:23:45 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	launch_proc_ext(pid_t pid)
{
	int		status;
	pid_t	wpid;

	wpid = 0;
	if (pid < 0)
		ft_putendl_fd("fork err: pid < 0", 2);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
}

int			launch_proc(char **args, char **paths, char *str, int i)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
	{
		if (execve(args[0], args, g_env->c_env) == -1)
		{
			if (search_key(g_env->vault, "PATH") != NULL)
				paths = ft_strsplit(env_path("PATH"), ':');
			while (paths[++i] != NULL)
			{
				str = ft_strjoiner(paths[i], args[0]);
				if (execve(str, args, g_env->c_env) != -1)
					return (1);
				free(str);
			}
			ft_printf("minishell: command not found: %s\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else
		launch_proc_ext(pid);
	return (1);
}

static char	*read_ln_ext(char *buffer, int pos, int c, int buffsize)
{
	while (1)
	{
		c = getchar();
		if (c == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		else if (c == EOF)
		{
			ft_putstr("\nTerminated by user\n");
			exit(-111);
		}
		else
			buffer[pos] = c;
		pos++;
		if (pos >= buffsize)
		{
			buffsize += BUFF_LN;
			buffer = ft_realloc(buffer, pos, buffsize);
			if (!buffer)
				exit(-8);
		}
	}
}

char		*read_ln(void)
{
	int		pos;
	int		buffsize;
	char	*buffer;
	int		c;

	pos = 0;
	c = 0;
	buffsize = BUFF_LN;
	buffer = ft_memalloc(buffsize);
	if (!buffer)
	{
		ft_putendl_fd("minishell: couldn't allocate memory", 2);
		exit(-8);
	}
	return (read_ln_ext(buffer, pos, c, buffsize));
}
