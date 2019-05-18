#include "minishell.h"

void	shell_init()
{
	clear();
	printf("\n\n\n\n******************"
		   "****************************");
	printf("\n\n\n\t*******MINISHELL PROJECT*******");
	printf("\n\n\t-school 21 unix branch project-");
	printf("\n\t-use   at  your  own  risk  :D-");
	printf("\n\n\n\n*******************"
		   "***************************");
	char* username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
	sleep(3);
	clear();
}

void	shell_loop(void) {
	char *line;
	char **args;
	int status;

	//read the commands of user
	//parse commands (PC differ command and args)
	//execute command

//	shell_init();
	g_env = environ_grab();

	status = 1;


	while (status) {
		ft_printf("$> ");
		line = read_ln();
		args = line_split(line, SPLIT_DELIM);
		status = launch_dispatcher(args);
//		environ_grab();
		free(line);
		free(args);
//		break ;

	}
}

static char *extract_path(char *str, char *key)
{
	int len;
	int i;
	int j;
	char *path;

	len = ft_strlen(str);
	i = ft_strlen(key) + 1;
	j = 0;
	path = ft_memalloc(len);
	while (str[i] != '\0')
	{
		path[j] = str[i];
		i++;
		j++;
	}
	path[j] = '\0';
	return (path);
}

char 	*env_path(char *key)
{
	int i;
	char *path;

	i = 0;
	while (g_env[i] != NULL)
	{
		if (ft_strstr(g_env[i], key))
		{
//			printf("%s\n", g_env[i]);
			path = extract_path(g_env[i], key);
			return (path);
		}
		i++;
	}
	return (0);
}


int		main(int argc, char **argv)
{
	char *str;
	char *path;
	char **pathes;
//	t_env	*env;


	//load the config

	//run REPL loop (read, evaluate, print loop)
//	shell_loop();

	g_env = environ_grab();
//	path = env_path("PATH");
//	printf("%s", path);

	pathes = ft_strsplit(env_path("PATH"), ':');

	int i = 0;
	while (pathes[i] != NULL)
	{
		printf("%s\n",pathes[i]);
		i++;
	}

//	int i = 0;

//	while (g_env[i] != NULL)
//	{
//		printf("%s\n",g_env[i]);
//		i++;
//	}

//	char* home = getenv("HOME");
//	printf("\n\n\nHOME is: %s", home);

	//Remove leaks. Clean up
	return (0);
}