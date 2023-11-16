#include "shell.h"

/**
 * builtins_list - Search for a match and execute the associated builtin.
 * @data: Struct for the program's data.
 *
 * Return: Always 0
 */

int builtins_list(data_of_program *data)
{
int k;
builtins options[] = {
{"exit", builtin_exit},
{"help", builtin_help},
{"cd", builtin_cd},
{"alias", builtin_alias},
{"env", builtin_env},
{"setenv", builtin_set_env},
{"unsetenv", builtin_unset_env},
{NULL, NULL}
};

for (k = 0; options[k].builtin != NULL; k++)
{
if (str_compare(options[k].builtin, data->command_name, 0))
{
return (options[k].function(data));
}
}
return (-1);
}
