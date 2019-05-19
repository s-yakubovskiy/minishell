#include "minishell.h"

//functions declaration
int cd_shell(char **args);
int help_shell(char **args);
int exit_shell(char **args);

// built-ins commands
char	*builtin_str[] = {
		"cd",
		"help",
		"exit"
};

int		(*builtin_func[]) (char **) = {
		&cd_shell,
		&help_shell,
		&exit_shell
};

int		num_shell_functions()
{
	return (sizeof(builtin_str) / sizeof(char *));
}


int		cd_shell(char **args)
{
	if (args[1] == NULL)
		chdir(env_path("HOME"));
	else if (chdir(args[1]) != 0)
	{
		if (args[1][0] == '~' && args[1][1] == '\0')
		{
			chdir(env_path("HOME"));
		}
		else if (args[1][0] == '-' && args[1][1] == '\0')
			chdir(env_path("OLDPWD"));
		else
			ft_putendl_fd("minishell chdir err", 2);
	}
	return 1;
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
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
		i++;
	}
	return (launch_proc(args));
}