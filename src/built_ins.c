/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:53:07 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/09 14:23:42 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			help_shell(process *proc)
{
	int i;

	ft_printf("21shell of 21's school project\n");
	ft_printf("Built-in commands (input argument if needed):\n");
	i = 0;
	while (i < NR_BUILTINS)
	{
		ft_printf("\t -> %s\n", shell->builtins->builtin_str[i]);
		i++;
	}
	ft_printf("For additional info -> use \"man\".\n");
	return (1);
}

int			exit_shell(process *proc)
{
	printf("say-o-nara~\n");
    exit(1);
//    return (1);
}


int			echo(process *proc)
{
    int i;

    i = 1;
    string_var_parser(proc->argv);
    while (proc->argv[i] != 0)
    {
        ft_printf("%s ", proc->argv[i]);
        i++;
    }
    ft_printf("\n");
    return (1);
}



int			cd_shell(process *proc)
{
    if (proc->argc == 1)
    {
        chdir(shell->pw_dir);
        sh_update_cwd_info();
        return (0);
    }
    if (chdir(proc->argv[1]) == 0)
    {
        sh_update_cwd_info();
        return (0);
    } else
    {
        printf("21sh: cd %s: No such file or directory\n", proc->argv[1]);
        return (0);
    }
}