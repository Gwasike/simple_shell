#include "shell.h"

/**
 * env_get_key - Retrieves the value of an environment variable.
 * @key: The environment variable of interest.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
char *env_get_key(char *key, data_of_program *data)
{
int k, key_length = 0;

if (key == NULL || data->env == NULL)
{
return (NULL);
}

key_length = str_length(key);

for (k = 0; data->env[k]; k++)
{

if (str_compare(key, data->env[k], key_length) &&
data->env[k][key_length] == '=')
{
return (data->env[k] + key_length + 1);
}
}

return (NULL);
}

/**
 * env_set_key - Overwrites/Creates the value of the environment variable
 * @key: Name of the variable to set.
 * @value: New value.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
int env_set_key(char *key, char *value, data_of_program *data)
{
int k, key_length = 0, is_new_key = 1;

if (key == NULL || value == NULL || data->env == NULL)
{
return (1);
}

key_length = str_length(key);

for (k = 0; data->env[k]; k++)
{
if (str_compare(key, data->env[k], key_length) &&
data->env[k][key_length] == '=')
{
is_new_key = 0;
free(data->env[k]);
break;
}
}
data->env[k] = str_concat(str_duplicate(key), "=");
data->env[k] = str_concat(data->env[k], value);

if (is_new_key)
{
data->env[k + 1] = NULL;
}
return (0);
}

/**
 * env_remove_key - Removes a key from the environment.
 * @key: The key to remove.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
int env_remove_key(char *key, data_of_program *data)
{
int k, key_length = 0;

if (key == NULL || data->env == NULL)
{
return (0);
}

key_length = str_length(key);

for (k = 0; data->env[k]; k++)
{
if (str_compare(key, data->env[k], key_length) &&
data->env[k][key_length] == '=')
{
free(data->env[k]);

k++;
for (; data->env[k]; k++)
{
data->env[k - 1] = data->env[k];
}

data->env[k - 1] = NULL;
return (1);
}
}
return (0);
}

/**
 * print_environ - Prints the current environment variables.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
void print_environ(data_of_program *data)
{
int m;

for (m = 0; data->env[m]; m++)
{
_print(data->env[m]);
_print("\n");
}
}
