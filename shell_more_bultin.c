#include "shell.h"

/**
 * builtin_exit - Exit the program with the status.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */
int builtin_exit(data_of_program *data)
{
int k;

if (data->tokens[1] != NULL)
{

for (k = 0; data->tokens[1][k]; k++)
if ((data->tokens[1][k] < '0' || data->tokens[1][k] > '9')
&& data->tokens[1][k] != '+')
{

errno = 2;
return (2);
}
errno = convert_str_to_int(data->tokens[1]);
}
free_all_data(data);
exit(errno);
}

/**
 * builtin_cd - Change the current directory.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */
int builtin_cd(data_of_program *data)
{
char *dir_home = get_environment_value("HOME", data), *dir_old = NULL;
char old_dir[128] = {0};
int error_code = 0;

if (data->tokens[1])
{
if (string_compare(data->tokens[1], "-", 0))
{
dir_old = get_environment_value("OLDPWD", data);
if (dir_old)
{
error_code = set_work_directory(data, dir_old);
}
write_to_stdout(get_environment_value("PWD", data));
write_to_stdout("\n");

return (error_code);
}
else
{
return (set_work_directory(data, data->tokens[1]));
}
}
else
{
if (!dir_home)
{
dir_home = getcwd(old_dir, 128);
}

return (set_work_directory(data, dir_home));
}
return (0);
}

/**
 * set_work_directory - Set the working directory.
 * @data: Struct for the program's data.
 * @new_dir: Path to be set as the working directory.
 *
 * Return: Always 0
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
char old_dir[128] = {0};
int err_code = 0;

getcwd(old_dir, 128);

if (!string_compare(old_dir, new_dir, 0))
{
err_code = chdir(new_dir);
if (err_code == -1)
{
errno = 2;
return (3);
}
set_env_key("PWD", new_dir, data);
}
set_env_key("OLDPWD", old_dir, data);
return (0);
}

/**
 * builtin_help - Display help information for builtins.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */
int builtin_help(data_of_program *data)
{
int k, length = 0;
char *messages[6] = {NULL};

messages[0] = HELP_MSG;

if (data->tokens[1] == NULL)
{
write_to_stdout(messages[0] + 6);
return (1);
}
if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}

messages[1] = HELP_EXIT_MSG;
messages[2] = HELP_ENV_MSG;
messages[3] = HELP_SETENV_MSG;
messages[4] = HELP_UNSETENV_MSG;
messages[5] = HELP_CD_MSG;

for (k = 0; messages[k]; k++)
{
length = string_length(data->tokens[1]);
if (string_compare(data->tokens[1], messages[k], length))
{
write_to_stdout(messages[k] + length + 1);
return (1);
}
}

errno = EINVAL;
perror(data->command_name);
return (0);
}

/**
 * builtin_alias - Add, remove, or show aliases.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */
int builtin_alias(data_of_program *data)
{
int k = 0;

if (data->tokens[1] == NULL)
{
return (print_alias(data, NULL));
}

while (data->tokens[++k])
{

if (count_characters(data->tokens[k], "="))
{
set_alias(data->tokens[k], data);
}
else
{
print_alias(data, data->tokens[k]);
}
}

return (0);
}
