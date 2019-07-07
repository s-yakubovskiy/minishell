//
// Created by Yoshiko Harwyn hoare on 2019-07-03.
//

#include "minishell.h"

int			release_job(int id)
{
	job		*job;
	process *proc;
	process *tmp;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	job = shell->jobs[id];
	proc = job->root;
	while (proc != NULL)
	{
		tmp = proc->next;
		free(proc->command);
		free(proc->argv);
		free(proc->input_path);
		free(proc->output_path);
		free(proc);
		proc = tmp;
	}
	free(job->command);
	free(job);
	return (0);
}


int			remove_job(int id)
{
	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	release_job(id);
	shell->jobs[id] = NULL;

	return (0);
}

int			insert_job(job *job)
{
	int id;

	id = get_next_job_id();
	if (id < 0)
		return -1;
	job->id = id;
	shell->jobs[id] = job;
	return (id);
}

int			get_next_job_id(void)
{
	int		i;

	i = 0;
	while (++i <= NR_JOBS)
		if (shell->jobs[i] == NULL)
			return (i);
	return (-1);
}

int			print_processes_of_job(int id)
{
	process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	printf("[%d]", id);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		proc = proc->next;
		printf(" %d", proc->pid);
	}
	printf("\n");
	return (0);
}


int			wait_for_job(int id)
{
	int		proc_count;
	int		wait_pid;
	int		wait_count;
	int		status;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	proc_count = get_proc_count(id, PROC_FILTER_REMAINING);
	wait_pid = -1;
	wait_count = 0;
	status = 0;

	while (wait_count <= proc_count)
	{
		wait_pid = waitpid(-shell->jobs[id]->pgid, &status, WUNTRACED);
		wait_count++;
		if (WIFEXITED(status))
			set_process_status(wait_pid, STATUS_DONE);
		else if (WIFSIGNALED(status))
			set_process_status(wait_pid, STATUS_TERMINATED);
		else if (WSTOPSIG(status))
		{
			status = -1;
			set_process_status(wait_pid, STATUS_SUSPENDED);
			if (wait_count == proc_count)
				print_job_status(id);
		}
	}
	return status;
}

int get_proc_count(int id, int filter)
{
	int		count;
	process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	count = 0;
	proc = shell->jobs[id]->root;
	while(proc != NULL)
	{
		if (filter == PROC_FILTER_ALL ||
			(filter == PROC_FILTER_DONE && proc->status == STATUS_DONE) ||
			(filter == PROC_FILTER_REMAINING && proc->status != STATUS_DONE)) {
			count++;
		}
		proc = proc->next;
	}
	return (count);
}


int set_process_status(int pid, int status)
{
	int		i;
	process	*proc;

	i = 0;
	while (++i <= NR_JOBS)
	{
		if (shell->jobs[i] == NULL)
			continue;
		proc = shell->jobs[i]->root;
		while (proc != NULL)
		{
			if (proc->pid == pid)
			{
				proc->status = status;
				return (0);
			}
			proc = proc->next;
		}
	}
	return (-1);
}

int print_job_status(int id)
{
	process *proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	printf("[%d]", id);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		printf("\t%d\t%s\t%s", proc->pid,
			   "STATUS STRING HERE", proc->command);
		if (proc->next != NULL)
			printf("|\n");
		else
			printf("\n");
		proc = proc->next;
	}
	return (0);
}