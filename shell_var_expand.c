#include "shell.h"

/**
 * expand_variables - Expands variables.
 * @data: A pointer to a struct of the program's data.
 *
 * Return: Always 0
 */
void expand_variables(data_of_program *data)
{
int k, m;
char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
{
return;
}
buffer_add(line, data->input_line);
for (k = 0; line[k]; k++)
{
if (line[k] == '#')
{
line[k--] = '\0';
}
else if (line[k] == '$' && line[k + 1] == '?')
{
line[k] = '\0';
convert_long_to_string(errno, expansion, 10);
buffer_add(line, expansion);
buffer_add(line, data->input_line + k + 2);
}
else if (line[k] == '$' && line[k + 1] == '$')
{
line[k] = '\0';
convert_long_to_string(getpid(), expansion, 10);
buffer_add(line, expansion);
buffer_add(line, data->input_line + k + 2);
}
else if (line[k] == '$' && (line[k + 1] == ' ' || line[k + 1] == '\0'))
{
continue;
}
else if (line[k] == '$')
{
for (m = 1; line[k + m] && line[k + m] != ' '; m++)
{
expansion[m - 1] = line[k + m];
}
expansion[m - 1] = '\0';
temp = get_environment_value(expansion, data);
line[k] = '\0';
buffer_add(line, line + k + m);
temp ? buffer_add(line, temp) : 1;
buffer_add(line, expansion);
}
}
if (!string_compare(data->input_line, line, 0))
{
free(data->input_line);
data->input_line = string_duplicate(line);
}
}

/**
 * expand_alias - Expands aliases.
 * @data: A pointer to a struct of the program's data.
 *
 * Return: Always 0
 */
void expand_alias(data_of_program *data)
{
int k, m, was_expanded = 0;
char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
{
return;
}
buffer_add(line, data->input_line);
for (k = 0; line[k]; k++)
{
for (m = 0; line[k + m] && line[k + m] != ' '; m++)
{
expansion[m] = line[k + m];
}
expansion[m] = '\0';
temp = alias_get(data, expansion);
if (temp)
{
expansion[0] = '\0';
buffer_add(expansion, line + k + m);
line[k] = '\0';
buffer_add(line, temp);
line[string_length(line)] = '\0';
buffer_add(line, expansion);
was_expanded = 1;
}
break;
}
if (was_expanded)
{
free(data->input_line);
data->input_line = string_duplicate(line);
}
}

/**
 * buffer_add - Appends a string at the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be copied to the buffer.
 *
 * Return: Always 0
 */
int buffer_add(char *buffer, char *str_to_add)
{
int length, k;
length = string_length(buffer);
for (k = 0; str_to_add[k]; k++)
{
buffer[length + k] = str_to_add[k];
}
buffer[length + k] = '\0';
return (length + k);
}
