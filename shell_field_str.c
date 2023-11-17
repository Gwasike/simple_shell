#include "shell.h"

/**
 * str_length - returns the length of a string.
 * @str: pointer to string.
 * Return: The length of string.
 */
int str_length(char *str)
{
int length = 0;

if (str == NULL)
{
return (0);
}

while (str[length++] != '\0')
{
}
return (--length);
}

/**
 * str_duplicate - duplicates a string
 * @str: String to be copied
 *
 * Return: Always 0
 */
char *str_duplicate(char *str)
{
char *result;
int length, i;

if (str == NULL)
{
return (NULL);
}

length = str_length(str) + 1;

result = malloc(sizeof(char) * length);

if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}
for (i = 0; i < length ; i++)
{
result[i] = str[i];
}

return (result);
}

/**
 * str_compare - Compare two strings
 * @s1: String one, or the shorter
 * @s2: String two, or the longer
 * @num: number of characters to be compared, 0 if infinite
 *
 * Return: Always 0
 */
int str_compare(char *s1, char *s2, int num)
{
int iterator;

if (s1 == NULL && s2 == NULL)
{
return (1);
}

if (s1 == NULL || s2 == NULL)
{
return (0);
}

if (num == 0)
{
if (str_length(s1) != str_length(s2))
{
return (0);
}
for (iterator = 0; s1[iterator]; iterator++)
{
if (s1[iterator] != s2[iterator])
{
return (0);
}
}
return (1);
}
else
{
for (iterator = 0; iterator < num ; iterator++)
{
if (s1[iterator] != s2[iterator])
{
return (0);
}
}
return (1);
}
}

/**
 * str_concat - concatenates two strings.
 * @s1: String to be concatenated
 * @s2: String to be concatenated
 *
 * Return: Always 0
 */
char *str_concat(char *s1, char *s2)
{
char *result;
int length1 = 0, length2 = 0;

if (s1 == NULL)
{
s1 = "";
}
length1 = str_length(s1);

if (s2 == NULL)
{
s2 = "";
}
length2 = str_length(s2);

result = malloc(sizeof(char) * (length1 + length2 + 1));
if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}

for (length1 = 0; s1[length1] != '\0'; length1++)
{
result[length1] = s1[length1];
}
free(s1);

for (length2 = 0; s2[length2] != '\0'; length2++)
{
result[length1] = s2[length2];
length1++;
}

result[length1] = '\0';
return (result);
}

/**
 * str_reverse - reverses a string.
 * @str: pointer to string.
 * Return: Always 0
 */
void str_reverse(char *str)
{
int k = 0, length = str_length(str) - 1;
char hold;

while (k < length)
{
hold = str[k];
str[k++] = str[length];
str[length--] = hold;
}
}
