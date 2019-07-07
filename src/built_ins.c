/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:53:07 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/05/20 21:55:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			help_shell(char **args)
{
	int i;
	int len;

	len = ft_strlen(args[0]);
	ft_printf("Minishell 21's school project\n");
	ft_printf("Built-in commands (input argument if needed):\n");
	i = 0;
	while (i < num_shell_functions())
	{
		ft_printf("\t -> %s\n", g_env->builtin_str[i]);
		i++;
	}
	ft_printf("For additional info -> use \"man\".\n");
	return (1);
}

int			exit_shell(char **args)
{
	return (1);
}

int			set_env(char **args)
{
	t_vault	*key;
	char	buf[50];

	if (args[1] == NULL || args[2] != NULL)
		ft_putendl_fd("minishell: setenv needs one argument {key=value}", 2);
	else
	{
		strcpy_till_n(buf, args[1], '=');
		key = search_key(g_env->vault, buf);
		if (key != NULL)
			remove_any_env(g_env->vault, key);
		g_env->vault = append_env(g_env->vault, args[1]);
		g_env->update_envv();
	}
	return (1);
}

int			unset_env(char **args)
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
			g_env->update_envv();
		}
	}
	return (1);
}

int			launch_dispatcher(char **args)
{
	int		i;
	int		j;
	char	**paths;
	char	*str;

	i = 0;
	j = -1;
	str = NULL;
	paths = NULL;
	if (args[0] == NULL)
		return (1);
	while (i < num_shell_functions())
	{
		if (strcmp(args[0], g_env->builtin_str[i]) == 0)
		{
			if (ft_strequ("env", args[0]))
			{
				g_env->print_envv(g_env->vault, display_env);
				return (1);
			}
			return (*g_env->builtin_func[i])(args);
		}
		i++;
	}
	return (launch_proc(args, paths, str, j));
}
