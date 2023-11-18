#include "shell.h"

/**
 * check_file - checks if a file exists, if it is not a directory, and
 * if it has execution permissions.
 * @full_path: pointer to the full file name
 *
 * Return: Always 0
 */
int check_file(char *full_path);

/**
 * find_program - find a program in the PATH.
 * @data: a pointer to the program's data
 *
 * Return: Always 0
 */
int find_program(data_of_program *data)
{
int k = 0, ret_code = 0;
char **directories;

if (!data->command_name)
{
return (2);
}
if (data->command_name[0] == '/' || data->command_name[0] == '.')
{
return (check_file(data->command_name));
}
free(data->tokens[0]);
data->tokens[0] = string_concatenate(string_duplicate("/"), data->command_name);
if (!data->tokens[0])
{
return (2);
}

directories = tokenize_path(data);

if (!directories || !directories[0])
{
errno = 127;
return (127);
}
for (k = 0; directories[k]; k++)
{
directories[k] = string_concatenate(directories[k], data->tokens[0]);
ret_code = check_file(directories[k]);
if (ret_code == 0 || ret_code == 126)
{
errno = 0;
free(data->tokens[0]);
data->tokens[0] = string_duplicate(directories[k]);
free_array_of_pointers(directories);
return (ret_code);
}
}
free(data->tokens[0]);
data->tokens[0] = NULL;
free_array_of_pointers(directories);
return (ret_code);
}

/**
 * tokenize_path - tokenize the PATH in directories.
 * @data: a pointer to the program's data
 *
 * Return: ALways 0
 */
char **tokenize_path(data_of_program *data)
{
int k = 0;
int counter_directories = 2;
char **tokens = NULL;
char *PATH;

PATH = get_environment_value("PATH", data);
if ((PATH == NULL) || PATH[0] == '\0')
{
return (NULL);
}
PATH = string_duplicate(PATH);
for (k = 0; PATH[k]; k++)
{
if (PATH[k] == ':')
{
counter_directories++;
}
}

tokens = malloc(sizeof(char *) * counter_directories);

k = 0;
tokens[k] = string_duplicate(_strtok(PATH, ":"));
while (tokens[k++])
{
tokens[k] = string_duplicate(_strtok(NULL, ":"));
}

free(PATH);
PATH = NULL;
return (tokens);
}

/**
 * check_file - checks if a file exists
 * @full_path: pointer to the full file name
 *
 * Return: Always 0
 */
int check_file(char *full_path)
{
struct stat sb;

if (stat(full_path, &sb) != -1)
{
if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
{
errno = 126;
return (126);
}
return (0);
}
errno = 127;
return (127);
}
