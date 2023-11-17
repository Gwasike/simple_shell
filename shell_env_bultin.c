#include "shell.h"

/**
 * builtin_env - Display the environment where the shell runs.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */
int builtin_env(data_of_program *data)
{
int k;
char cpname[50] = {'\0'};
char *var_copy = NULL;

if (data->tokens[1] == NULL)
{
print_environ(data);
}
else
{
for (k = 0; data->tokens[1][k]; k++)
{
if (data->tokens[1][k] == '=')
{
var_copy = str_duplicate(env_get_key(cpname, data));
if (var_copy != NULL)
{
env_set_key(cpname, data->tokens[1] + k + 1, data);
}
print_environ(data);
if (env_get_key(cpname, data) == NULL)
{
_print(data->tokens[1]);
_print("\n");
}
else
{
env_set_key(cpname, var_copy, data);
free(var_copy);
}
return (0);
}
cpname[k] = data->tokens[1][k];
}
errno = 2;
perror(data->command_name);
errno = 127;
}
return (0);
}

/**
 * builtin_set_env - Set or update environment variables.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */

int builtin_set_env(data_of_program *data)
{
if (data->tokens[1] == NULL || data->tokens[2] == NULL)
{
return (0);
}
if (data->tokens[3] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}

env_set_key(data->tokens[1], data->tokens[2], data);

return (0);
}

/**
 * builtin_unset_env - Unset environment variables.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */

int builtin_unset_env(data_of_program *data)
{
if (data->tokens[1] == NULL)
{
return (0);
}
if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}
env_remove_key(data->tokens[1], data);

return (0);
}
