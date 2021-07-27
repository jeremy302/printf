
#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdarg.h>

#ifndef NULL
#define NULL
#endif

#define FLAGS_COUNT 5

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef unsigned short ushort;

/**
 * struct FormatOptions - structure of a format option
 * @flags: an array of all flags (unique)
 * @width: minimum width (defaults to 0);
 * @precision: floats precision(defaults to 6, or 0 in the case of only ".")
 * @length: data-type length modifier
 * @specifier: type of output
 */
typedef struct FormatOptions
{
	char flags[FLAGS_COUNT];
	uint width;
	uint precision;
	char length;
	char specifier;
} FormatOptions;

uint put_char(char c, char flush);
uint put_str(char *str);
void put_char_repeat(char c, uint count);
unsigned int put_char_str(char *str, char specifier);
int _printf(const char *format, ...);

uint str_len(char *str);
int str_has_char(char *src, char c);
uint str_add_unique_char(char *str, char c);

uint num_to_str(long num, uchar base, char *out, uchar lower, int sig0);
uint unum_to_str(ulong num, uchar base, char *out, uchar lower, int sig0);

int max(int a, int b);
ulong read_arg(FormatOptions *opt, va_list *args);

uint print_format(const char *format, va_list *args, uint *cursor);
uint print_uint_format(FormatOptions *options, ulong args);
uint print_int_format(FormatOptions *options, ulong args);
uint print_str_format(FormatOptions *options, ulong args);
uint print_pointer_format(FormatOptions *opt, ulong args);

#endif
