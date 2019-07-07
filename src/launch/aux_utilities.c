//
// Created by Yoshiko Harwyn hoare on 2019-07-03.
//

#include "minishell.h"

int 		len_two_dim(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*helper_strtrim(char* line)
{
	char	*head;
	char	*tail;

	head = line;
	tail = line + strlen(line) - 1;
	while (*head == ' ')
		head++;
	while (*tail == ' ')
		tail--;
	*(tail + 1) = '\0';
	return (head);
}

void check_zombie()
{
	int status;
	int pid;

//	while ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED|WCONTINUED)) > 0)
//	{
//		if (WIFEXITED(status)) {
//			set_process_status(pid, STATUS_DONE);
//		} else if (WIFSTOPPED(status)) {
//			set_process_status(pid, STATUS_SUSPENDED);
//		} else if (WIFCONTINUED(status)) {
//			set_process_status(pid, STATUS_CONTINUED);
//		}
//
//		int job_id = get_job_id_by_pid(pid);
//		if (job_id > 0 && is_job_completed(job_id)) {
//			print_job_status(job_id);
//			remove_job(job_id);
//		}
//	}
}


int execute_builtin_command(process *proc)
{

	if (proc->type == COMMAND_EXIT)
		;
	else if (proc->type == COMMAND_CD)
		;




//	while (i < num_shell_functions())
//	{
//		if (strcmp(args[0], g_env->builtin_str[i]) == 0)
//		{
//			if (ft_strequ("env", args[0]))
//			{
//				g_env->print_envv(g_env->vault, display_env);
//				return (1);
//			}
//			return (*g_env->builtin_func[i])(args);
//		}
//		i++;
//	}
	else
		return (1);
	return (0);
}