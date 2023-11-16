#include "shell.h"

/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @k: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: Always 0
*/
int check_logic_ops(char *array_commands[], int k, char array_operators[])
{
char *temp = NULL;
int j;

for (j = 0; array_commands[k] != NULL  && array_commands[k][j]; j++)
{
if (array_commands[k][j] == '&' && array_commands[k][j + 1] == '&')
{
temp = array_commands[k];
array_commands[k][j] = '\0';
array_commands[k] = str_duplicate(array_commands[k]);
array_commands[k + 1] = str_duplicate(temp + j + 2);
k++;
array_operators[k] = '&';
free(temp);
j = 0;
}
if (array_commands[k][j] == '|' && array_commands[k][j + 1] == '|')
{
temp = array_commands[k];
array_commands[k][j] = '\0';
array_commands[k] = str_duplicate(array_commands[k]);
array_commands[k + 1] = str_duplicate(temp + j + 2);
k++;
array_operators[k] = '|';
free(temp);
j = 0;
}
}
return (k);
}

/**
* _getline - read one line from the prompt.
* @data: struct for the program's data.
*
* Return: Always 0
*/
int _getline(data_of_program *data)
{
char buff[BUFFER_SIZE] = {'\0'};
static char *array_commands[10] = {NULL};
static char array_operators[10] = {'\0'};
ssize_t bytes_read, k = 0;

if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
(array_operators[0] == '|' && errno == 0))
{

for (k = 0; array_commands[k]; k++)
{
free(array_commands[k]);
array_commands[k] = NULL;
}

bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
if (bytes_read == 0)
{
return (-1);
}

k = 0;
do {
array_commands[k] = str_duplicate(_strtok(k ? NULL : buff, "\n;"));
k = check_logic_ops(array_commands, k, array_operators);
} while (array_commands[k++]);
}

data->input_line = array_commands[0];
for (k = 0; array_commands[k]; k++)
{
array_commands[k] = array_commands[k + 1];
array_operators[k] = array_operators[k + 1];
}

return (str_length(data->input_line));
}
