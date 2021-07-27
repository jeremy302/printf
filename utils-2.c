#include "holberton.h"

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
 * read_arg - reads the next argument from `args`
 * @opt: format option
 * @args: argument list to read from
 *
 * Return: the next argument in `args`
 */
ulong read_arg(FormatOptions *opt, va_list *args)
{
	if (str_has_char("xXuo", opt->specifier))
		return (opt->length == 'h' ? (ushort)va_arg(*args, uint)
		: opt->length == 'l' ? (ulong)va_arg(*args, ulong)
				: (uint)va_arg(*args, uint));
	else if (str_has_char("di", opt->specifier))
		return (opt->length == 'h' ? (short)va_arg(*args, int) :
				opt->length == 'l' ? (long)va_arg(*args, long) :
				(int)va_arg(*args, int));
	else if (str_has_char("sSrRc", opt->specifier))
		return (str_has_char("sSrR", opt->specifier) ?
				(ulong)va_arg(*args, char *) : va_arg(*args, int));

	return (va_arg(*args, int));
}
/**
 * print_pointer_format - prints a pointer with the given format
 * @opt: format options
 * @args: the pointer
 *
 * Return: characters printer
 */
uint print_pointer_format(FormatOptions *opt, ulong args)
{
	ulong arg = args;
	static char nil[20] = "(nil)";

	if (arg == 0)
		return (opt->specifier = 's', print_str_format(opt, (ulong)nil));
	opt->specifier = 'x', str_add_unique_char(
		opt->flags, '#'), opt->length = 'l';
	return (print_uint_format(opt, args));
}
