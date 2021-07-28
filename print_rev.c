#include "holberton.h"

/**
 * print_rev - Print a string in reverse
 * @1: arg
 * @f: Pointer to the struct
 * Return: length of printed string
 */
int print_rev(va_list 1, mods*f)
{
	register short len = 0, j;
	char *s = va_arg(1, char *);

	(void)f;
	if (!s)
		s = NULL_STRING;
	while (s[len])
		len++;
	for (j = len -1;j >= o; j--)
		put_char(s[j]);

	return (len);
}
