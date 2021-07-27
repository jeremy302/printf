#include "holberton.h"
#include <unistd.h>

/**
 * str_len - calculates the length of a string
 * @str: a string
 *
 * Return: `str`'s length
 */
unsigned int str_len(char *str)
{
	unsigned int len = 0;

	if (str != NULL)
		while (str[len])
			len++;
	return (len);
}

/**
 * str_has_char - checks if `c` is in `src`
 * @src: string to check
 * @c: character to look for
 *
 * Return: 1 if `c` is in `src`, else 0
 */
int str_has_char(char *src, char c)
{
	unsigned int i;

	if (src != NULL)
		for (i = 0; src[i]; i++)
			if (src[i] == c)
				return (1);
	return (0);
}

/**
 * str_add_unique_char - adds `c` to `str` if it isn't in `str`
 * @str: a string
 * @c: a character
 *
 * Return: the index of `c`
 */
unsigned int str_add_unique_char(char *str, char c)
{
	unsigned int i;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == c)
			return (i);
	str[i] = c;
	str[i + 1] = '\0';
	return (i);
}


/**
 * unum_to_str - converts an usigned integer to a string
 * @num: integer to convert
 * @base: base to convert `num` to
 * @out: buffer to write to ('\0' is appended)
 * @lower: determines if the letters used would be in a lower/upper case
 * @sig0: determines if the last insignificant 0 is printed
 *
 * Return: the length of the string (exlcuding '\0')
 */
uint unum_to_str(ulong num, uchar base, char *out, uchar lower, int sig0)
{
	unsigned int i;
	char c;

	if (base < 2 || base > 36 || out == NULL)
		return (0);
	c = num % base;
	c = c > 9 ? (lower ? 'a' + (c - 10) : 'A' + (c - 10)) : c + '0';
	if (num / base == 0)
	{
		if (c != '0' || sig0)
			*out++ = c;
		*out = '\0';
		return (c == '0' ? !!sig0 : 1);
	}
	i = unum_to_str(num / base, base, out, lower, sig0);
	out[i] = c;
	out[i + 1] = '\0';
	return (i + 1);
}
/**
 * num_to_str - converts a signed integer to a string
 * @num: integer to convert
 * @base: base to convert `num` to
 * @out: buffer to write to ('\0' is appended)
 * @lower: determines if the letters used would be in a lower/upper case
 * @sig0: determines if the last insignificant 0 is printed
 *
 * Return: the length of the string (exlcuding '\0')
 */
uint num_to_str(long num, uchar base, char *out, uchar lower, int sig0)
{
	if (base > 36 || out == NULL)
		return (0);
	if (num < 0)
		return (unum_to_str((num + 1) * -1 + 1, base, out, lower, sig0));
	return (unum_to_str((unsigned long) num, base, out, lower, sig0));
}
