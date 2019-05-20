#include "minishell.h"

//void	shell_init()
//{
//	clear();
//	printf("\n\n\n\n******************"
//		   "****************************");
//	printf("\n\n\n\t*******MINISHELL PROJECT*******");
//	printf("\n\n\t-school 21 unix branch project-");
//	printf("\n\t-use   at  your  own  risk  :D-");
//	printf("\n\n\n\n*******************"
//		   "***************************");
//	char* username = getenv("USER");
//	printf("\n\n\nUSER is: @%s", username);
//	printf("\n");
//	sleep(3);
//	clear();
//}

void	shell_loop(void)
{
	char *line;
	char **args;
	int status;
	t_vault *ptr;

	//read the commands of user
	//parse commands (PC differ command and args)
	//execute command

//	shell_init();



	status = 1;


	while (status) {
		signal(SIGINT, signal_handler);
		ft_printf("$> ");
//		gotoxy(0, 0);
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
	t_vault	*ptr;

	ptr = search_key(g_env->vault, key);

	return (ptr->path);
}

void	env_init(t_vault *ptr)
{
	g_env = malloc(sizeof(t_env));
	g_env->c_env = ft_memalloc(sizeof(char*) * 300);
	g_env->c_env[g_env->index] = ft_memalloc(300);
	g_env->index = 0;
	g_env->vault = ptr;
	g_env->updateEnv = update_env;
	g_env->printEnv = traverse;
	g_env->getDir = get_cwd;
	g_env->getDir(search_key(g_env->vault, "PWD")->path);
	g_env->getDir(search_key(g_env->vault, "OLDPWD")->path);
}

void	get_cwd(char *str)
{
	char cwd[256];

	if (chdir(".") != 0)
		ft_putendl_fd("chdir() error()", 2);
	else {
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			ft_putendl_fd("getcwd() error", 2);
		else
		{
			ft_strclr(str);
			ft_strcpy(str, cwd);
		}
	}
}

int		main(int argc, char **argv)
{
	t_vault *ptr;


	ptr = NULL;
	ptr = environ_grab(ptr);
	env_init(ptr);
	traverse(g_env->vault, grab_vault);

//	printf("%s", g_env->c_env[5]);
	t_vault *search;

	search = search_key(g_env->vault, "OLDPWD");
//	printf("%s\n", g_env->curPwd);



//	char **str;
//
//	str = line_split("   $HOME  is nice $PWD '$HELLO' to $SMTH   ", SPLIT_DELIM);
//
//	int i = 0;
//	while (str[i] != 0)
//	{
//		printf("%s\n", str[i]);
//		i++;
//	}
//	string_var_parser(str);
//
//
//	while (str[i] != 0)
//	{
//		printf("%s\n", str[i]);
//		i++;
//	}

	//load the config

	//run REPL loop (read, evaluate, print loop)
	shell_loop();
//








	//remove leaks
	return (0);
}
