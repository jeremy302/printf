#include "holberton.h"
#include <unistd.h>

/**
 * put_char - write the character to stdout
 * @c: char
 * Return: on success 1, otherwise -1
 */
int _putchar(char c)
{
	static char buf[KILOBYTE];
	static int i;

	if (c == FLUSH || >= KILOBYTE)
	{
		write(1, &buf, i);
		i = 0;
	}
	else
	{
		buf[i] =c;
		i++;
	}
	return (1);
}

/**
 * _puts - Prints a string
 * @str: Pointer to string
 * Return: number of chars written
 */
int _puts(char *str)
{
	register short i;

	for (i = 0; str[i]; i++)
		puts_char(str[i]);
	return (i);
}
