#include "shell.h"

/**
 * split_string - Splits the string into parts
 * @data: a pointer to the program's data
 *
 * Return: Always 0
 */
void split_string(data_of_program *data)
{
char *delimiter = " \t";
int k, m, counter = 2, length;

length = str_length(data->input_line);
if (length)
{
if (data->input_line[length - 1] == '\n')
{
data->input_line[length - 1] = '\0';
}
}

for (k = 0; data->input_line[k]; k++)
{
for (m = 0; delimiter[m]; m++)
{
if (data->input_line[k] == delimiter[m])
{
counter++;
}
}
}

data->tokens = malloc(counter *sizeof(char *));
if (data->tokens == NULL)
{
perror(data->program_name);
exit(errno);
}

k = 0;
data->tokens[k] = str_duplicate(_strtok(data->input_line, delimiter));
data->command_name = str_duplicate(data->tokens[0]);

while (data->tokens[k++])
{
data->tokens[k] = str_duplicate(_strtok(NULL, delimiter));
}
}
