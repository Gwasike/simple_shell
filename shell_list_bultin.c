#include "shell.h"

/**
 * builtins_list - Search and execute the associated builtin.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */

int builtins_list(data_of_program *data)
{
int k;
builtins options[] = {
{"exit", exitCommand},
{"help", built_help_inf},
{"cd", cdCommand},
{"alias", builtinAlias},
{"env", execute_builtin_env},
{"setenv", execute_builtin_set_env},
{"unsetenv", execute_builtin_unset_env},
{NULL, NULL}
};

for (k = 0; options[k].builtin != NULL; k++)
{
if (string_compare(options[k].builtin, data->command_name, 0))
{
return (options[k].function(data));
}
}
return (-1);
}
