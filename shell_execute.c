#include "shell.h"

/**
 * execute_var - Executes a command with its entire path variables.
 * @data: A pointer to the program's data.
 *
 * Return: Always 0
 */
int execute_var(data_of_program *data)
{
int a = 0, status;
pid_t pid;
a = builtins_list(data);
if (a != -1)
{
return (a);
}
a = find_program(data);
if (a)
{
return (a);
}
else
{
pid = fork();
if (pid == -1)
{
perror(data->command_name);
exit(EXIT_FAILURE);
}
if (pid == 0)
{
a = execve(data->tokens[0], data->tokens, data->env);
if (a == -1)
{
perror(data->command_name), exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
if (WIFEXITED(status))
{
errno = WEXITSTATUS(status);
}
else if (WIFSIGNALED(status))
{
errno = 128 + WTERMSIG(status);
}
}
}
return (0);
}
