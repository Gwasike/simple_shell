#include "shell.h"

/**
 * get_environment_value - Retrieves the value of an environment variable.
 * @key: The environment variable of interest.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
char *get_environment_value(char *key, data_of_program *data)
{
int k, key_length = 0;

if (key == NULL || data->env == NULL)
{
return (NULL);
}

key_length = string_length(key);

for (k = 0; data->env[k]; k++)
{

if (string_compare(key, data->env[k], key_length) &&
data->env[k][key_length] == '=')
{
return (data->env[k] + key_length + 1);
}
}

return (NULL);
}

/**
 * set_env_key - Overwrites/Creates the value of the environment variable
 * @key: Name of the variable to set.
 * @value: New value.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
int set_env_key(char *key, char *value, data_of_program *data)
{
int k, key_length = 0, is_new_key = 1;

if (key == NULL || value == NULL || data->env == NULL)
{
return (1);
}

key_length = string_length(key);

for (k = 0; data->env[k]; k++)
{
if (string_compare(key, data->env[k], key_length) &&
data->env[k][key_length] == '=')
{
is_new_key = 0;
free(data->env[k]);
break;
}
}
data->env[k] = string_concatenate(string_duplicate(key), "=");
data->env[k] = string_concatenate(data->env[k], value);

if (is_new_key)
{
data->env[k + 1] = NULL;
}
return (0);
}

/**
 * remove_env_key - Removes a key from the environment.
 * @key: The key to remove.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
int remove_env_key(char *key, data_of_program *data)
{
int k, key_length = 0;

if (key == NULL || data->env == NULL)
{
return (0);
}

key_length = string_length(key);

for (k = 0; data->env[k]; k++)
{
if (string_compare(key, data->env[k], key_length) &&
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
 * printEnv - Prints the current environment variables.
 * @data: Struct holding the program's data.
 *
 * Return: Always 0
 */
void printEnv(data_of_program *data)
{
int m;

for (m = 0; data->env[m]; m++)
{
write_to_stdout(data->env[m]);
write_to_stdout("\n");
}
}
