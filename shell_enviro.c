#include "shell.h"

/**
 * my_environment - prints the current environment
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */

int my_environment(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
 * get_enviro - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: Always 0
 */

char *get_enviro(info_t *info, const char *name)
{
list_t *node = info->env;
char *g;

while (node)
{
g = starts_with(node->str, name);
if (g && *g)
{
return (g);
}
node = node->next;
}
return (NULL);
}

/**
 * set_environment - Initialize a new environment variable
 * @info: A pointer to info_t structure
 *
 * Return: Always 0
 */

int set_environment(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (set_envron(info, info->argv[1], info->argv[2]))
{
return (0);
}
return (1);
}

/**
 * unset_environment - Removes environment variable
 * @info: A pointer to the info_t structure
 *
 * Return: Always 0
 */

int unset_environment(info_t *info)
{
int k;

if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (k = 1; k <= info->argc; k++)
{
unset_envron(info, info->argv[k]);
}

return (0);
}

/**
 * initialize_environment - files env linked list
 * @info: A pointer to info_t structure
 *
 * Return: Always 0
 */

int initialize_environment(info_t *info)
{
list_t *node = NULL;
size_t k;

for (k = 0; environ[k]; k++)
{
add_node_end(&node, environ[k], 0);
}
info->env = node;
return (0);
}
