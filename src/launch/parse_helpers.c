#include "minishell.h"



int			get_command_type(char *command)
{
	if (strcmp(command, "exit") == 0)
	    return COMMAND_EXIT;
    else if (strcmp(command, "help") == 0)
        return COMMAND_HELP;
	else if (strcmp(command, "cd") == 0)
		return COMMAND_CD;
	else if (strcmp(command, "jobs") == 0)
		return COMMAND_JOBS;
	else if (strcmp(command, "fg") == 0)
		return COMMAND_FG;
	else if (strcmp(command, "bg") == 0)
		return COMMAND_BG;
	else if (strcmp(command, "kill") == 0)
		return COMMAND_KILL;
	else if (strcmp(command, "export") == 0)
		return COMMAND_EXPORT;
	else if (strcmp(command, "unset") == 0)
		return COMMAND_UNSET;
	else
		return COMMAND_EXTERNAL;
}




int		parse_cycle(process *new_proc, char **tokens, int i, int position)
{
	while (i < position)
	{
		if (tokens[i][0] == '<')
		{
			if (strlen(tokens[i]) == 1)
			{
				new_proc->input_path = ft_memalloc(PATH_BUFSIZE);
				strcpy(new_proc->input_path, tokens[i + 1]);
				i++;
			}
			else
			{
				new_proc->input_path = ft_memalloc(PATH_BUFSIZE);
				strcpy(new_proc->input_path, tokens[i] + 1);
			}
		}
		else if (tokens[i][0] == '>')
		{
			if (strlen(tokens[i]) == 1)
			{
				new_proc->output_path = ft_memalloc(PATH_BUFSIZE);
				strcpy(new_proc->output_path, tokens[i + 1]);
				i++;
			}
			else
			{
				new_proc->output_path = ft_memalloc(PATH_BUFSIZE);
				strcpy(new_proc->output_path, tokens[i] + 1);
			}
		}
		else
			break ;
		i++;
	}
	return (position);
}


void		parse_helper2(process *new_proc, char **tokens, char *segment)
{
	int i;
	int position;
	int argc;

	position = len_two_dim(tokens);
	i = 0;
	while (i < position)
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			break;
		i++;
	}
	argc = i;
	position = parse_cycle(new_proc, tokens, i, position);
	i = argc;
	while (i <= position)
		tokens[i++] = NULL;
	new_proc->command = segment;
	new_proc->argv = tokens;
	new_proc->argc = argc;
	new_proc->pid = -1;
	new_proc->type = get_command_type(tokens[0]);
	new_proc->next = NULL;
}


process		*shell_parse_command_segment(char *segment)
{
	char	**tokens;
	process	*new_proc;

	tokens = line_split(segment, SPLIT_DELIM);
	if (!tokens)
	{
		fprintf(stderr, "21sh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	new_proc = (process*)malloc(sizeof(process));
	new_proc->output_path = NULL;
	new_proc->input_path = NULL;
	parse_helper2(new_proc, tokens, segment);
	return new_proc;
}



void carry_init(g_parse *carry, char *line)
{
	line = helper_strtrim(line);
	carry->command = strdup(line);
	carry->line_cursor = line;
	carry->c = line;
	carry->seg = NULL;
	carry->seg_len = 0;
	carry->mode = FOREGROUND_EXECUTION;

	if (line[strlen(line) - 1] == '&')
	{
		carry->mode = BACKGROUND_EXECUTION;
		line[strlen(line) - 1] = '\0';
	}
}


static job *job_init(g_parse *carry, job *new_job, process *root_proc)
{
	new_job->root = root_proc;
	new_job->command = carry->command;
	new_job->pgid = -1;
	new_job->mode = carry->mode;

	return (new_job);
}

job			*shell_parse_command(char *line)
{
	process *root_proc;
	process *proc;
	g_parse *carry;
	job		*new_job;

	carry = (g_parse*)malloc(sizeof(g_parse));
	new_job = (job*)malloc(sizeof(job));
	carry_init(carry, line);
	root_proc = NULL;
	proc = NULL;
	while (1)
	{
		if (*(carry->c) == '\0' || *(carry->c) == '|')
		{
			carry->seg = (char*)malloc((carry->seg_len + 1) * sizeof(char));
			strncpy(carry->seg, carry->line_cursor, carry->seg_len);
			carry->seg[carry->seg_len] = '\0';
			carry->new_proc = shell_parse_command_segment(carry->seg);
			if (!root_proc)
			{
				root_proc = carry->new_proc;
				proc = root_proc;
			}
			else
			{
				proc->next = carry->new_proc;
				proc = carry->new_proc;
			}
			if (*(carry->c) != '\0')
			{
				carry->line_cursor = carry->c;
				while (*(++(carry->line_cursor)) == ' ')
					;
				carry->c = carry->line_cursor;
				carry->seg_len = 0;
				continue ;
			}
			else
				break ;
		}
		else
		{
			carry->seg_len++;
			(carry->c)++;
		}
	}
	new_job = job_init(carry, new_job, root_proc);
	return new_job;
}