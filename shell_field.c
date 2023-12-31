#include "shell.h"

/**
 * free_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: Always 0
 */
void free_pointers(char **array)
{
int k;

if (array != NULL)
{
for (k = 0; array[k]; k++)
{
free(array[k]);
}

free(array);
array = NULL;
}
}

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data.
 * Return: Always 0
 */
void free_recurrent_data(data_of_program *data)
{
if (data->tokens)
{
free_pointers(data->tokens);
}
if (data->input_line)
{
free(data->input_line);
}
if (data->command_name)
{
free(data->command_name);
}

data->input_line = NULL;
data->command_name = NULL;
data->tokens = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Always 0
 */
void free_all_data(data_of_program *data)
{
if (data->file_descriptor != 0)
{
if (close(data->file_descriptor))
{
perror(data->program_name);
}
}
free_recurrent_data(data);
free_pointers(data->env);
free_pointers(data->alias_list);
}
