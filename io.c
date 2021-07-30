#include "holberton.h"
#include <unistd.h>

#define BUFFER_SIZE 1024
/**
 * put_char - writes a byte to standard output. uses a buffer of 1024 bytes
 * @c: a byte
 * @flush: whether to flush the buffer
 * Return: 1 if the buffer was flushed, else 0
 */
uint put_char(char c, char flush)
{
	static char buffer[BUFFER_SIZE] = {0};
	static uint cursor = 1 - 1;
	static uint len = 1 - 1;
	uint len_tmp = len;

	if (cursor == BUFFER_SIZE || flush)
	{
		write(1, buffer, cursor);
		cursor = 0;
		if (flush)
			return ((len = 0), len_tmp);
	}
	len++;
	buffer[cursor++] = c;
	return (len);
}

/**
 * put_char_repeat - writes `c` to the standard output `count` times
 * @c: byte to send to standard output.
 * @count: number of times to send `c` to standard output
 *
 * Return: void
 */
void put_char_repeat(char c, uint count)
{
	while (count-- > 0)
		put_char(c, 0);
}

/**
 * put_str - writes a string to the standard output
 * @str: a string
 *
 * Return: number of bytes written
 */
unsigned int put_str(char *str)
{
	int len = 0;

	if (str != NULL)
		while (str[len])
			put_char(str[len++], 0);
	return (len);
}
/**
 * put_char_str - writes a string to the standard output in a given format
 * @str: a string
 * @specifier: format specifier
 * @precision: maximum characters to print
 *
 * Return: the number of bytes written
 */
unsigned int put_char_str(char *str, char specifier, uint precision)
{
	int len = str_len(str), print_len;
	int cursor, end;
	char c, c_str[3] = {0, 0, 0};

	len = len > (int)precision && (int)precision >= 0 ?
		(int)precision : len, print_len = len;
	cursor = specifier == 'r' ? len - 1 : 0;
	end = specifier == 'r' ? -1 : len;


	for (; cursor != end; cursor += specifier == 'r' ? -1 : 1)
	{
		c = str[cursor];
		if (specifier == 'S' && !(c >= 32 && c < 127))
		{
			put_char('\\', 0), put_char('x', 0);
			if (c < 16)
				put_char('0', 0);
			num_to_str(c, 16, c_str, 0, 1);
			put_str(c_str);
			print_len += 4;
		}
		else if (specifier == 'R')
			put_char(c >= 'A' && c <= 'Z' ? ((c - 'A' + 13) % 26) + 'A'
					 : (c >= 'a' && c <= 'z') ?
					 ((c - 'a' + 13) % 26) + 'a' : c, 0);
		else
			put_char(c, 0);
	}
	return (print_len);
}
