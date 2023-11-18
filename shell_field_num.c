#include "shell.h"

/**
 * convert_long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number.
 *
 * Return: Always 0
 */
void convert_long_to_string(long number, char *string, int base)
{
int index = 0, inNegative = 0;
long cociente = number;
char letters[] = {"0123456789abcdef"};

if (cociente == 0)
{
string[index++] = '0';
}

if (string[0] == '-')
{
inNegative = 1;
}

while (cociente)
{
if (cociente < 0)
{
string[index++] = letters[-(cociente % base)];
}
else
{
string[index++] = letters[cociente % base];
}
cociente /= base;
}
if (inNegative)
{
string[index++] = '-';
}

string[index] = '\0';
string_reverse(string);
}

/**
 * convert_str_to_int - convert a str to an int
 * @a: pointer to str origen.
 *
 * Return: Always 0
 */
int convert_str_to_int(char *a)
{
int sign = 1;
unsigned int number = 0;

while (!('0' <= *a && *a <= '9') && *a != '\0')
{
if (*a == '-')
{
sign *= -1;
}
if (*a == '+')
{
sign *= +1;
}
a++;
}

while ('0' <= *a && *a <= '9' && *a != '\0')
{

number = (number * 10) + (*a - '0');
a++;
}
return (number *sign);
}

/**
 * count_characters - count the coincidences of character in string.
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 *
 * Return: Always 0
 */
int count_characters(char *string, char *character)
{
int k = 0, counter = 0;

for (; string[k]; k++)
{
if (string[k] == character[0])
{
counter++;
}
}
return (counter);
}
