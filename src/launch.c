#include "minishell.h"

extern char **environ;
//	char *args[2];
//	args[0] = "/bin/ls";
//	args[1] = "-lh";
//	execve(args[0], args, NULL);



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
	paths = ft_strsplit(env_path("PATH"), ':');
	i = 0;
	if (pid == 0)
	{
		// new process
//		if (execvp(args[0], args) == -1)
//			printf("minishell: command not found: %s\n", args[0]);
		if (execve(args[0], args, vault->arr) == -1)
		{
			while (paths[i] != NULL)
			{
				str = ft_strjoiner(paths[i], args[0]);
				if (execve(str, args, environ) != -1)
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

void	environ_grab()
{
	extern char **environ;
//	char **env;
	int i = 0;
	char *key;
	char *path;

	while (environ[i] != NULL)
	{
		append_env(g_env, environ[i]);
//		ft_strcpy(env[i], environ[i]);
		i++;

	}
//	return (env);

}




//void	environ_grab()
//{
//
//	int i = 0;
//
//	while (environ[i] != NULL)
//	{
//		if (ft_strstr(environ[i], "ZSH"))
//			printf("%s\n",environ[i]);
////		printf("%s\n",environ[i]);
//		i++;
//	}
//
//
//}