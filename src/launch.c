#include "minishell.h"


//	char *args[2];
//	args[0] = "/bin/ls";
//	args[1] = "-lh";
//	execve(args[0], args, NULL);



int launch_proc(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char 	**pathes;
	int		i;

	pid = fork();
	pathes = ft_strsplit(env_path("PATH"), ':');
	i = 0;
	if (pid == 0)
	{
		// new process
//		if (execvp(args[0], args) == -1)
//			printf("minishell: command not found: %s\n", args[0]);
		if (execve(args[0], args, g_env) == -1)
		{
			while (pathes[i] != NULL)
			{
				if (execve(args[0], args, g_env) != -1)
				{

				}
				i++;
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

char	**environ_grab()
{
	extern char **environ;
	char **env;
	int i = 0;

	env = ft_memalloc(300);
	while (environ[i] != NULL)
	{
		env[i] = ft_memalloc(500);
		ft_strcpy(env[i], environ[i]);
		i++;

	}
	env[i] = 0;
	return (env);

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