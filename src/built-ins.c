#include "minishell.h"

//functions declaration
int cd_shell(char **args);
int help_shell(char **args);
int exit_shell(char **args);
int set_env(char **args);
int unset_env(char **args);
int echo(char **args);

// built-ins commands
char	*builtin_str[] = {
		"cd",
		"help",
		"exit",
		"env",
		"setenv",
		"unsetenv",
		"echo"
};

int		(*builtin_func[]) (char **) = {
		&cd_shell,
		&help_shell,
		&exit_shell,
		&set_env,
		&set_env,
		&unset_env,
		&echo
};

int		num_shell_functions()
{
	return (sizeof(builtin_str) / sizeof(char *));
}



int		echo(char **args)
{
	int i;

	i = 1;
	string_var_parser(args);
//	printf("hello");

//	printf("%s", args[2]);
//
	while (args[i] != 0)
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
	return (1);
}




int		cd_shell(char **args)
{
	char buf[256];
	char path[256];
	int	i;

	i = 1;
	path[0] = 0;
	if (args[1] == NULL)
	{
		chdir(env_path("HOME"));
		g_env->getDir(search_key(g_env->vault, "PWD")->path);
	}
	else if (args[1][0] != '-')
		g_env->getDir(search_key(g_env->vault, "OLDPWD")->path);
	else if (chdir(args[1]) != 0)
	{
		if (args[1][0] == '~')
		{
			chdir(env_path("HOME"));
			if (args[1][1] == '/')
			{
				while (args[1][++i] != '\0')
					path[i - 2] = args[1][i];
				path[i - 2] = '\0';
				if (chdir(path) != 0)
					ft_putendl_fd("minishell: chdir err", 2);
			}
			g_env->getDir(search_key(g_env->vault, "PWD")->path);
		}
		else if (args[1][0] == '-')
		{
			g_env->getDir(buf);
			chdir(env_path("OLDPWD"));

			if (args[1][1] == '/')
			{
				while (args[1][++i] != '\0')
					path[i - 2] = args[1][i];
				path[i - 2] = '\0';
				if (chdir(path) != 0)
					ft_putendl_fd("minishell: chdir err", 2);
			}
			g_env->getDir(search_key(g_env->vault, "PWD")->path);
			ft_strclr(search_key(g_env->vault, "OLDPWD")->path);
			ft_strcpy(search_key(g_env->vault, "OLDPWD")->path, buf);
		}
		else
			ft_putendl_fd("minishell: chdir err", 2);
	}
	g_env->getDir(search_key(g_env->vault, "PWD")->path);
	return (1);
}

int		help_shell(char **args)
{
	int i;

	printf("Minishell 21's school project\n");
	printf("Built-in commands (input argument if needed):\n");

	i = 0;
	while (i < num_shell_functions())
	{
		printf("\t -> %s\n", builtin_str[i]);
		i++;
	}

	printf("For additional info -> use \"man\".\n");
	return (1);
}

int		exit_shell(char **args)
{
	return (0);
}


int		set_env(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
		ft_putendl_fd("minishell: setenv needs one argument {key=value}", 2);
	else
	{
		g_env->vault = append_env(g_env->vault, args[1]);
		g_env->updateEnv();
	}
	return (1);
}

int		unset_env(char **args)
{
	t_vault *key;

	if (args[1] == NULL || args[2] != NULL)
		ft_putendl_fd("minishell: unsetenv needs one argument", 2);
	else
	{
		key = search_key(g_env->vault, args[1]);
		if (key == NULL)
			ft_putendl_fd("minishell: couldn't find ENV", 2);
		else
		{
			g_env->vault = remove_any_env(g_env->vault, key);
			g_env->updateEnv();
		}
	}
	return (1);
}


int		launch_dispatcher(char **args)
{
	int i;

	i = 0;
	if (args[0] == NULL)
	{
		return (1); // empty line
	}

	while (i < num_shell_functions())
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			if (ft_strequ("env", args[0]))
			{
				g_env->printEnv(g_env->vault, display_env);
				return(1);
			}
			return (*builtin_func[i])(args);
		}
		i++;
	}
	return (launch_proc(args));
}