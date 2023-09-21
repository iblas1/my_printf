#include "main.h"
/**
 * printf_handler - Prints an argument based on its type
 * @fmtt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @din: din.
 * @letter: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @letter_size: Size specifier
 * Return: 1 or 2;
 */
int printf_handler(const char *fmtt, int *din, va_list list, char letter[],
	int flags, int width, int precision, int letter_size)
{
	int i, unknown_len = 0, printed_characters = -1;
	fmtt_t fmt_types[] = {
		{'c', printf_character}, {'s', printf_string}, {'%', printf_percentage},
		{'i', printf_integer}, {'d', printf_integer}, {'b', printf_binary},
		{'u', printf_unsigned}, {'o', printf_octal}, {'x', printf_hexadecimal},
		{'X', printf_hexa_upper}, {'p', printf_pointer}, {'S', printf_non_printable},
		{'r', printf_reverse}, {'R', printf_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmtt != '\0'; i++)
	if (fmtt[*din] == fmt_types[i].fmtt)
	return (fmt_types[i].f(list, letter, flags, width, precision, letter_size));

	if (fmt_types[i].fmtt == '\0')
	{
		if (fmtt[*din] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmtt[*din - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*din);
			while (fmtt[*din] != ' ' && fmtt[*din] != '%')
				--(*din);
			if (fmtt[*din] == ' ')
				--(*din);
			return (1);
		}
		unknown_len += write(1, &fmtt[*din], 1);
		return (unknown_len);
	}
	return (printed_characters);
}
