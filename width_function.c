#include "main.h"

/**
 * printf_get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int printf_get_width(const char *format, int *i, va_list list)
{
	int current_j;
	int w = 0;

	for (current_j = *i + 1; format[current_j] != '\0'; current_j++)
	{
		if (is_digitf(format[current_j]))
		{
			w *= 10;
			w += format[current_j] - '0';
		}
		else if (format[current_j] == '*')
		{
			current_j++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_j - 1;

	return (w);
}
