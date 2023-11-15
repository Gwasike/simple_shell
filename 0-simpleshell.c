#include "shell.h"
#include <stdio.h>

/**
 * main - code that passes the betty checks
 *
 * Return: Always 0
 */

int main(void)
{
pid_t child_pid;
int status;

child_pid = fork();
if (child_pid == -1)
{
perror("fork error");
exit(EXIT_FAILURE);
}

if (child_pid == 0)
{
write(STDOUT_FILENO, "Child process\n", 14);
_exit(EXIT_SUCCESS);
}
else
{
waitpid(child_pid, &status, 0);
if (WIFEXITED(status))
{
write(STDOUT_FILENO, "Parent process\n", 15);
}
else
{
write(STDERR_FILENO, "Child process did not exit normally\n", 36);
}
}
return (0);
}
