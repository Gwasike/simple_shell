#include "shell.h"

/**
 * get_environstr - returns the string array copy of our environ
 * @info: A pointer to the info_t structure
 *
 * Return: Always 0
 */
char **get_environstr(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
 * unset_envron - Remove an environment variable
 * @info: Pointer to the structure
 * @var: the string env var property
 *
 * Return: Always 0
 */

int unset_envron(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *g;

if (!node || !var)
{
return (0);
}
while (node)
{
g = starts_with(node->str, var);
if (g && *g == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
 * set_envron - Creates a new environment variable
 * @info: Pointer in info_t structure
 * @var: The string env var property
 * @value: The string
 *
 *  Return: Always 0
 */

int set_envron(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *g;

if (!var || !value)
{
return (0);
}

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
{
return (1);
}
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = info->env;
while (node)
{
g = starts_with(node->str, var);
if (g && *g == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
