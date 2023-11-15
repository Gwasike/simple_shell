#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct myshell_fields - contains various fields representing a different piece of information
 * @argc: the count of arguements
 * @arg: string that containns the arguements
 * @argv: array of arg strings
 * @path: pointer to the string repsenting the path
 * @err_num: represents an error number
 * @linecount_flag: integer flag indicates whether the counting is active
 * @line_count: represents the line count
 * @fname: pointer thst represents a file name
 * @alias: pointer to a linked list
 * @env: represents environment variables
 * @history: represents the command history
 * @environ: pointer to array of strings representing the environment
 * @status: represennts the status
 * @env_changed: inticates whether the environment variable has changed
 * @cmd_buf: pointer to array of strings representing a commnand buffer
 * @readfd: represents a file discriptor for reading
 * @histcount: An integer representing the history count
 */

typedef struct myshell_fields
{
int argc;
char *arg;
char **argv;
char *path;
int err_num;
int linecount_flag;
unsigned int line_count;
char *fname;
list_t *alias;
list_t *env;
list_t *history;
char **environ;
int status;
int env_changed;
char cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{\
0,
NULL,
NULL,
NULL,
0,
0,
0,
NULL,
NULL,
NULL,
NULL,
NULL,
0,
0,
NULL,
0,
0,
0
}


// Task 0
int main(void);

#endif
