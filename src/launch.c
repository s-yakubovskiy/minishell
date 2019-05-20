#include "minishell.h"

int launch_proc(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char 	**paths;
	int		i;
	char	*str;

	pid = fork();
	signal(SIGINT, proc_signal_handler);

	i = 0;
	if (pid == 0)
	{
//		 new process
		if (execve(args[0], args, g_env->c_env) == -1)
		{
			if (search_key(g_env->vault, "PATH") != NULL)
				paths = ft_strsplit(env_path("PATH"), ':');
			while (paths[i] != NULL)
			{
				str = ft_strjoiner(paths[i], args[0]);
				if (execve(str, args, g_env->c_env) != -1)
				{
					return(1);
				}
				i++;
				free(str);
			}

			printf("minishell: command not found: %s\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_putendl_fd("fork err: pid < 0", 2);  // fork error
	}
	else
	{

		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

t_vault		*environ_grab(t_vault *root)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		root = append_env(root, environ[i]);
		i++;
	}
	return (root);

}
