#include "holberton.h"
#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>

/*#define MAX(x,y) ((x) > (y) ? (x) : (y))*/

/**
 * max - returns the bigger of 2 integers
 * @a: an integer
 * @b: an integer
 *
 * Return: the highest parameters
 */
int max(int a, int b)
{
	return (a >= b ? a : b);
}

/**
 * print_int_format - prints an integer with the given options
 * @opt: Format Options
 * @args: pointer to a va_list object to get the argument from
 *
 * Return: number of bytes printed
 */
uint print_int_format(FormatOptions *opt, va_list *args)
{
	long arg = opt->length == 'h' ? (short)va_arg(*args, int) :
		opt->length == 'l' ? (long)va_arg(*args, long) : (int)va_arg(*args, int);
	char arg_str[12];
	char sign = arg < 0 ? '-' : str_has_char(opt->flags, '+') ?
		'+' : str_has_char(opt->flags, ' ') ? ' ' : 0;
	uint arg_len = num_to_str(arg, 10, arg_str, 1, opt->precision > 0) + !!sign;
	int zeros_len = max(opt->precision - (arg_len - !!sign), 0);
	int padding_len = max(opt->width - (zeros_len + arg_len), 0);

	if (str_has_char(opt->flags, '-'))
	{
		if (sign)
			put_char(sign, 0);
		put_char_repeat('0', zeros_len);
		put_str(arg_str);
		put_char_repeat(' ', padding_len);
	}
	else if (str_has_char(opt->flags, '0'))
	{
		if (zeros_len)
			put_char_repeat(' ', padding_len), sign ? put_char(sign, 0) :
				0, put_char_repeat('0', zeros_len), put_str(arg_str);
		else
			sign ? put_char(sign, 0) : 0,
				put_char_repeat('0', padding_len), put_str(arg_str);
	}
	else
	{
		put_char_repeat(' ', padding_len);
		if (sign)
			put_char(sign, 0);
		put_char_repeat('0', zeros_len);
		put_str(arg_str);
	}
	return (arg_len + padding_len);
}

/**
 * print_uint_format - prints an unsigned integer with the given options
 * @opt: Format Options
 * @args: pointer to a va_list object to get the argument from
 *
 * Return: number of bytes printed
 */
uint print_uint_format(FormatOptions *opt, va_list *args)
{
	ulong arg = opt->length == 'h' ? (ushort)va_arg(*args, uint)
		: opt->length == 'l' ? (ulong)va_arg(*args, ulong)
		: (uint)va_arg(*args, uint);
	char arg_str[8 * sizeof(uint) + 1];
	char *prefix = !str_has_char(opt->flags, '#') ? "" :
		opt->specifier == 'x' ? "0x" : opt->specifier == 'X' ?
		"0X" : opt->specifier == 'o' ? "0" : "";
	uchar base = str_has_char("xX", opt->specifier) ? 16 :
		opt->specifier == 'o' ? 8 : opt->specifier == 'b' ? 2 : 10;
	uint arg_len = unum_to_str(arg, base, arg_str,
							   opt->specifier == 'x', opt->precision > 0) + str_len(prefix);
	int zeros_len = max((opt->precision - (arg_len - str_len(prefix)) -
						 (opt->specifier == 'o' && str_has_char(opt->flags, '#'))), 0);
	int padding_len = max(opt->width - (zeros_len + arg_len), 0);

	if (str_has_char(opt->flags, '-'))
	{
		put_str(prefix);
		put_char_repeat('0', zeros_len);
		put_str(arg_str);
		put_char_repeat(' ', padding_len);
	}
	else if (str_has_char(opt->flags, '0'))
	{
		if (zeros_len)
			put_char_repeat(' ', padding_len), put_str(prefix),
				put_char_repeat('0', zeros_len), put_str(arg_str);
		else
			put_str(prefix), put_char_repeat('0', padding_len), put_str(arg_str);
	}
	else
	{
		put_char_repeat(' ', padding_len);
		put_str(prefix);
		put_char_repeat('0', zeros_len);
		put_str(arg_str);
	}
	return (arg_len + padding_len);
}

/**
 * print_str_format - prints a string with the given options
 * @opt: Format Options
 * @args: pointer to a va_list object to get the argument from
 *
 * Return: number of bytes printed
 */
uint print_str_format(FormatOptions *opt, va_list *args)
{
	char placeholder[] = "0";
	char *arg = str_has_char("sSrR", opt->specifier) ?
		va_arg(*args, char *) : placeholder;
	*placeholder = (opt->specifier == 'c') * va_arg(*args, int);
	uint cursor, arg_len = str_len(arg);
	uint padding_len;

	if (opt->specifier == 'S')
		for (cursor = 0; arg[cursor]; cursor++)
			if (!(arg[cursor] >= 32 && arg[cursor] < 127))
				arg_len += 2;
	padding_len = (opt->width > arg_len ? opt->width : arg_len) - arg_len;
	put_char_repeat(' ', padding_len * !str_has_char(opt->flags, '-'));
	put_char_str(arg, opt->specifier);
	put_char_repeat(' ', padding_len * str_has_char(opt->flags, '-'));
	return (arg_len + padding_len);
}

/**
 * print_format - parses a string format prints it with arguments from `*args`
 * @format: a string with the format
 * @args: pointer to a va_list object to get arguments from
 * @cursor: a pointer to a cursor. offsets it by the parsed format length
 *
 * Return: number of bytes written
 */
uint print_format(const char *format, va_list *args, uint *cursor)
{
	char *flags = "+ #0-", *lengths = "lh", *specifiers = "dicsbuoxXSprR";
	uint i = 0;
	FormatOptions *opt = malloc(sizeof(FormatOptions));

	opt->flags[0] = '\0', opt->width = 0, opt->precision =
		-1, opt->length = '\0', opt->specifier = '\0';
	while (str_has_char(flags, format[i]))
		str_add_unique_char(opt->flags, format[i++]);
	if (format[i] == '*')
		i++, opt->width = va_arg(*args, uint);
	else
		while (format[i] >= '0' && format[i] <= '9' &&
			   (opt->width < opt->width * 10 + (format[i] - '0')))
			opt->width = (opt->width) * 10 + (format[i++] - '0');
	if (format[i] == '.')
		opt->precision = 0;
	if (format[i] == '.' && format[i + 1] == '*')
		i += 2, opt->precision = va_arg(*args, uint);
	else if (format[i] == '.' && (format[i + 1] < '0' || format[i + 1] > '9'))
		i++, opt->precision = 0;
	else if (format[i] == '.')
		while (i++, format[i] >= '0' && format[i] <= '9' &&
			   opt->precision < opt->precision * 10 + (format[i] - '0'))
			opt->precision = opt->precision * 10 + (format[i] - '0');
	(str_has_char(lengths, format[i])) ? opt->length = format[i++] : 0;
	*cursor += i + 1;
	if (str_has_char(specifiers, format[i]))
	{
		opt->specifier = format[i];
		if (opt->specifier == 'p')
			opt->specifier = 'x', str_add_unique_char(
				opt->flags, '#'), opt->length = sizeof(void *) == 8 ? 'l' : '0';
		uint (*handler)(FormatOptions *opt, va_list *args) =
			str_has_char("di", opt->specifier) ? print_int_format
			: str_has_char("uoxXb", opt->specifier) ? print_uint_format
			: str_has_char("sSrR", opt->specifier) ? print_str_format : NULL;
		return (handler == NULL ? 1 : handler(opt, args));
	}
	else
		return (put_char('%', 0), 1);
}

/**
 * _printf - print a string after formatting arguments
 * @format: a string representing the format
 *
 * Return: number of bytes written to stdout
 */
int _printf(const char *format, ...)
{
	uint cursor = 0;
	uint len = 0;
	va_list args;

	va_start(args, format);
	while (format[cursor])
	{
		if (format[cursor] == '%')
			cursor++, len += print_format(format + cursor, &args, &cursor) + 1;
		else
			len++, put_char(format[cursor++], 0);
	}
	va_end(args);
	return (put_char(0, 1));
}
