#include "holnerton.h"

/**
 * _putchar - writes th character c to stdout
 * @c: The cjaracter to print
 *
 * Return: on Success 1.
 * On error, -1 is returned, and errno is set appropriately
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
