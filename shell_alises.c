#include "shell.h"

/**
 * print_alias - Display or manipulate aliases.
 * @data: Struct for the program's data.
 * @alias: Name of the alias to be printed.
 *
 * Return: Always 0
 */
int print_alias(data_of_program *data, char *alias)
{
int k, m, alias_length;
char buffer[250] = {'\0'};

if (data->alias_list)
{
alias_length = str_length(alias);
for (k = 0; data->alias_list[k]; k++)
{
if (!alias || (str_compare(data->alias_list[k], alias, alias_length)
&& data->alias_list[k][alias_length] == '='))
{
for (m = 0; data->alias_list[k][m]; m++)
{
buffer[m] = data->alias_list[k][m];
if (data->alias_list[k][m] == '=')
{
break;
}
}
buffer[m + 1] = '\0';
buffer_add(buffer, "'");
buffer_add(buffer, data->alias_list[k] + m + 1);
buffer_add(buffer, "'\n");
_print(buffer);
}
}
}

return (0);
}

/**
 * get_alias - Retrieve aliases.
 * @data: Struct for the program's data.
 * @name: Name of the requested alias.
 *
 * Return: Always 0
 */
char *get_alias(data_of_program *data, char *name)
{
int k, alias_length;

if (name == NULL || data->alias_list == NULL)
{
return (NULL);
}

alias_length = str_length(name);

for (k = 0; data->alias_list[k]; k++)
{

if (str_compare(name, data->alias_list[k], alias_length) &&
data->alias_list[k][alias_length] == '=')
{

return (data->alias_list[k] + alias_length + 1);
}
}

return (NULL);
}

/**
 * set_alias - Add or override aliases.
 * @alias_string: Alias to be set in the form (name='value').
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */
int set_alias(char *alias_string, data_of_program *data)
{
int k, m;
char buffer[250] = {'0'}, *temp = NULL;

if (alias_string == NULL ||  data->alias_list == NULL)
{
return (1);
}

for (k = 0; alias_string[k]; k++)
if (alias_string[k] != '=')
{
buffer[k] = alias_string[k];
}
else
{

temp = get_alias(data, alias_string + k + 1);
break;
}

for (m = 0; data->alias_list[m]; m++)
if (str_compare(buffer, data->alias_list[m], k) &&
data->alias_list[m][k] == '=')
{

free(data->alias_list[m]);
break;
}

if (temp)
{

buffer_add(buffer, "=");
buffer_add(buffer, temp);
data->alias_list[m] = str_duplicate(buffer);
}
else
{

data->alias_list[m] = str_duplicate(alias_string);
}
return (0);
}
