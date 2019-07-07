//
// Created by Yoshiko Harwyn hoare on 2019-06-19.
//

#ifndef SHELL_21_H
#define SHELL_21_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"

#define NR_JOBS 20
#define PATH_BUFSIZE 1024
#define COMMAND_BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

#define BACKGROUND_EXECUTION 0
#define FOREGROUND_EXECUTION 1
#define PIPELINE_EXECUTION 2

#define COMMAND_EXTERNAL 0
#define COMMAND_EXIT 1
#define COMMAND_CD 2
#define COMMAND_JOBS 3
#define COMMAND_FG 4
#define COMMAND_BG 5
#define COMMAND_KILL 6
#define COMMAND_EXPORT 7
#define COMMAND_UNSET 8

#define STATUS_RUNNING 0
#define STATUS_DONE 1
#define STATUS_SUSPENDED 2
#define STATUS_CONTINUED 3
#define STATUS_TERMINATED 4

#define PROC_FILTER_ALL 0
#define PROC_FILTER_DONE 1
#define PROC_FILTER_REMAINING 2

#define COLOR_NONE "\033[m"
#define COLOR_RED "\033[1;37;41m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_GREEN "\033[0;32;32m"
#define COLOR_GRAY "\033[1;30m"



//const char* STATUS_STRING[] = {
//		"running",
//		"done",
//		"suspended",
//		"continued",
//		"terminated"
//};



/*
** 				process and job
 * 				list structure
*/

typedef struct 			s_process
{
	char				*command;
	int					argc;
	char				**argv;
	char				*input_path;
	char				*output_path;
	pid_t				pid;
	int					type;
	int					status;
	struct s_process	*next;
}						process;

typedef struct			s_job
{
	int					id;
	process				*root;
	char				*command;
	pid_t				pgid;
	int					mode;
}						job;

typedef struct 			s_launch
{
	process				*proc;
	char				*seg;
	int 				job_id;
	int 				status;
	int 				in_fd;
	int 				out_fd;
	int 				fd[2];
} 						h_launch;


typedef struct 			s_shell_info
{
	char				cur_user[TOKEN_BUFSIZE];
	char				cur_dir[PATH_BUFSIZE];
	char				pw_dir[PATH_BUFSIZE];
	char 				**env;
	char 				**path;
	struct s_job		*jobs[NR_JOBS + 1];
//	struct h_launch		*launch_h;
} 						shell_info;

typedef struct 			s_parse
{
	char 				*command;
	char				*line_cursor;
	char				*c;
	char				*seg;
	int 				seg_len;
	int 				mode;
	struct s_process	*new_proc;
} 						g_parse;




shell_info	*shell;


/*
** 				aux utils
*/


int 				len_two_dim(char **str);


/*
** 				parsing part
*/

char				*helper_strtrim(char* line);
job					*shell_parse_command(char *line);
process				*shell_parse_command_segment(char *segment);
void				parse_helper2(process *new_proc, char **tokens, char *segment);
int					get_command_type(char *command);

void				carry_init(g_parse *carry, char *line);


/*
** 				job handlers
*/

int					get_next_job_id(void);
int					insert_job(job *job);
void				check_zombie(void);
int					remove_job(int id);
int					release_job(int id);
int					print_processes_of_job(int id);
int					wait_for_job(int id);
int					get_proc_count(int id, int filter);
/*
** 				launcher funcs
*/


int					shell_launch_job(job *job);
int					shell_launch_process(job *job, process *proc, int in_fd, int out_fd, int mode);
int					execute_builtin_command(process *proc);
int					set_process_status(int pid, int status);
int					print_job_status(int id);


#endif
