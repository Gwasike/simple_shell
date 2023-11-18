#include "shell.h"

/**
 * write_to_stdout - writes a array of chars in the standar output
 * @string: pointer to the array of chars.
 * Return: Always 0
 * On error, -1 is returned
 */
int write_to_stdout(char *string)
{
return (write(STDOUT_FILENO, string, string_length(string)));
}
/**
 * write_to_stderr - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 *
 * Return: Always 0
 * On error, -1 is returned
 */
int write_to_stderr(char *string)
{
return (write(STDERR_FILENO, string, string_length(string)));
}

/**
 * print_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: Always zero
 * On error, -1 is returned.
 */
int print_error(int errorcode, data_of_program *data)
{
char n_as_string[10] = {'\0'};
convert_long_to_string((long) data->exec_counter, n_as_string, 10);

if (errorcode == 2 || errorcode == 3)
{
write_to_stderr(data->program_name);
write_to_stderr(": ");
write_to_stderr(n_as_string);
write_to_stderr(": ");
write_to_stderr(data->tokens[0]);
if (errorcode == 2)
{
write_to_stderr(": Illegal number: ");
}
else
{
write_to_stderr(": can't cd to ");
}
write_to_stderr(data->tokens[1]);
write_to_stderr("\n");
}
else if (errorcode == 127)
{
write_to_stderr(data->program_name);
write_to_stderr(": ");
write_to_stderr(n_as_string);
write_to_stderr(": ");
write_to_stderr(data->command_name);
write_to_stderr(": not found\n");
}
else if (errorcode == 126)
{
write_to_stderr(data->program_name);
write_to_stderr(": ");
write_to_stderr(n_as_string);
write_to_stderr(": ");
write_to_stderr(data->command_name);
write_to_stderr(": Permission denied\n");
}
return (0);
}
