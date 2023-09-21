#include "main.h"

/**
 * printf_get_precision - Calculates the precise_location for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int printf_get_precision(const char *format, int *i, va_list list)
{
	int current_j = *i + 1;
	int precise_location = -1;

	if (format[current_j] != '.')
		return (precise_location);

	precise_location = 0;

	for (current_j += 1; format[current_j] != '\0'; current_j++)
	{
		if (is_digitf(format[current_j]))
		{
			precise_location *= 10;
			precise_location += format[current_j] - '0';
		}
		else if (format[current_j] == '*')
		{
			current_j++;
			precise_location = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_j - 1;

	return (precise_location);
}
