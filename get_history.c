#include "shell.h"

/**
 * get_history - gets the history file
 * @info: a pointer to the info_t structure
 *
 * Return: Always 0
 */

char *get_history(info_t, *info)
{
char *buf_fer *dir_ect;

dir_ect = _getenv(info, "HOME=");
if (!dir_ect)
{
return (NULL);
}

buf_fer = malloc(sizeof(char) * (_strlen(dir_ect) + _strlen(HIST_FILE) + 2));
if (!buf_fer)
{
return (NULL);
}
buf_fer[0] = 0;
_strcpy(buf_fer, dir_ect);
_strcat(buf_fer, "/");
_strcat(buf_fer, HIST_FILE);
return (buf_fer);
}

/**
 * print_history - prins the command history
 * @info: A pointer to the info_t structure
 *
 * Return: Always 0
 */

int print_history(info_t, *info)
{
ssize_t fd;
char *file_name = get_history(info);
list *node = NULL;

if (!file_name)
{
return (-1);
}
fd = open(file_name, O_CREAT | O_TRUNC | RDWR, 0644);
free(file_name);
if (fd = -1)
{
return (-1);
}
for (node = info->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * load_history - reads command history from a file
 * @info: A pointer to the info_t structure
 *
 * Return: Always 0
 */

int load_history(info_t, *info)
{
int k, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf_fer = NULL, *filename = get_history(info);

if (!filename)
{
return (0);
}

fd = open(filename, O_RDONLY);
free(filename);

if (fd == -1)
{
return (0);
}

if (!fstat(fd, &st))
{
fsize = st.st_size;
}

if (fsize < 2)
{
return (0);
}

buf_fer = malloc(sizeof(char) * (fsize + 1));
if (!buf_fer)
{
return (0);
}

rdlen = read(fd, buf_fer, fsize);
buf_fer[fsize] = 0;

if (rdlen <= 0)
{
return (free(buf_fer), 0);
}

close(fd);

for (k = 0; k < fsize; k++)
if (buf_fer[k] == '\n')
{
buf_fer[k] = 0;
update_history(info, buf_fer + last, linecount++);
last = k + 1;
}

if (last != k)
{
update_history(info, buf_fer + last, linecount++);
}

free(buf_fer);
info->histcount = linecount;

while (info->histcount-- >= HIST_MAX)
{
delete_node_at_index(&(info->history), 0);
}

renumber_history(info);
return (info->histcount);
}
}
