/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 19:18:37 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 20:45:19 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			num_shell_functions(void)
{
	return (7);
}

int			echo(char **args)
{
	int i;

	i = 1;
	string_var_parser(args);
	while (args[i] != 0)
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	ft_printf("\n");
	return (1);
}

static void	cd_shell_ext2(char **args, char *path, int i, char *buf)
{
	g_env->get_dir(buf);
	chdir(env_path("OLDPWD"));
	if (args[1][1] == '/')
	{
		while (args[1][++i] != '\0')
			path[i - 2] = args[1][i];
		path[i - 2] = '\0';
		if (chdir(path) != 0)
			ft_putendl_fd("minishell: chdir err", 2);
	}
	g_env->get_dir(search_key(g_env->vault, "PWD")->path);
	ft_strclr(search_key(g_env->vault, "OLDPWD")->path);
	ft_strcpy(search_key(g_env->vault, "OLDPWD")->path, buf);
}

static void	cd_shell_ext(char **args, char *path, int i, char *buf)
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
		g_env->get_dir(search_key(g_env->vault, "PWD")->path);
	}
	else if (args[1][0] == '-')
		cd_shell_ext2(args, path, i, buf);
	else
		ft_putendl_fd("minishell: chdir err", 2);
}

int			cd_shell(char **args)
{
	char	buf[256];
	char	path[256];
	int		i;

	i = 1;
	path[0] = 0;
	if (args[1] == NULL)
	{
		chdir(env_path("HOME"));
		g_env->get_dir(search_key(g_env->vault, "PWD")->path);
		return (1);
	}
	if (args[1][0] != '-')
		g_env->get_dir(search_key(g_env->vault, "OLDPWD")->path);
	if (chdir(args[1]) != 0)
		cd_shell_ext(args, path, i, buf);
	g_env->get_dir(search_key(g_env->vault, "PWD")->path);
	return (1);
}
