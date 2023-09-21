#include "main.h"

/**
 * printf_get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int printf_get_size(const char *format, int *i)
{
	int cur_printf_i = *i + 1;
	int amount = 0;

	if (format[cur_printf_i] == 'l')
		amount = PRINTS_LONG;
	else if (format[cur_printf_i] == 'h')
		amount = PRINTS_SHORT;

	if (amount == 0)
		*i = cur_printf_i - 1;
	else
		*i = cur_printf_i;

	return (amount);
}
