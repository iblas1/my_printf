#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * writef_char_handler - Prints a string
 * @c: char types.
 * @letter: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @letter_size: Size specifier
 *
 * Return: Number of chars printed.
 */
int writef_char_handler(char c, char letter[],
	int flags, int width, int precision, int letter_size)
{ /* char is stored at left and paddind at letter's right */
	int i = 0;
	char space = ' ';

	NONUSED(precision);
	NONUSED(letter_size);

	if (flags & PRINTF_ZERO)
		space = '0';

	letter[i++] = c;
	letter[i] = '\0';

	if (width > 1)
	{
		letter[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			letter[BUFFER_SIZE - i - 2] = space;

		if (flags & PRINTF_MINUS)
			return (write(1, &letter[0], 1) +
					write(1, &letter[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &letter[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &letter[0], 1));
	}

	return (write(1, &letter[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @letter: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @letter_size: Size specifier
 *
 * Return: Number of chars printed.
 */
int writef_number(int is_negative, int ind, char letter[],
	int flags, int width, int precision, int letter_size)
{
	int length = BUFFER_SIZE - ind - 1;
	char space = ' ', extra_ch = 0;

	NONUSED(letter_size);

	if ((flags & PRINTF_ZERO) && !(flags & PRINTF_MINUS))
		space = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & PRINTF_PLUS)
		extra_ch = '+';
	else if (flags & PRINTF_SPACE)
		extra_ch = ' ';

	return (writef_num(ind, letter, flags, width, precision,
		length, space, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the letter
 * @letter: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @space: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int writef_num(int ind, char letter[],
	int flags, int width, int prec,
	int length, char space, char extra_c)
{
	int j, space_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && letter[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFFER_SIZE - 2 && letter[ind] == '0')
		letter[ind] = space = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		space = ' ';
	while (prec > length)
		letter[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (j = 1; j < width - length + 1; j++)
			letter[j] = space;
		letter[j] = '\0';
		if (flags & PRINTF_MINUS && space == ' ')
		{
			if (extra_c)
				letter[--ind] = extra_c;
			return (write(1, &letter[ind], length) + write(1, &letter[1], j - 1));
		}
		else if (!(flags & PRINTF_MINUS) && space == ' ')
		{
			if (extra_c)
				letter[--ind] = extra_c;
			return (write(1, &letter[1], j - 1) + write(1, &letter[ind], length));
		}
		else if (!(flags & PRINTF_MINUS) && space == '0')
		{
			if (extra_c)
				letter[--space_start] = extra_c;
			return (write(1, &letter[space_start], j - space_start) +
				write(1, &letter[ind], length - (1 - space_start)));
		}
	}
	if (extra_c)
		letter[--ind] = extra_c;
	return (write(1, &letter[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the letter
 * @letter: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @letter_size: Size specifier
 *
 * Return: Number of written chars.
 */
int writef_unsgnd(int is_negative, int ind,
	char letter[],
	int flags, int width, int precision, int letter_size)
{

	int length = BUFFER_SIZE - ind - 1, i = 0;
	char space = ' ';

	NONUSED(is_negative);
	NONUSED(letter_size);

	if (precision == 0 && ind == BUFFER_SIZE - 2 && letter[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		space = ' ';

	while (precision > length)
	{
		letter[--ind] = '0';
		length++;
	}

	if ((flags & PRINTF_ZERO) && !(flags & PRINTF_MINUS))
		space = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			letter[i] = space;

		letter[i] = '\0';

		if (flags & PRINTF_MINUS)
		{
			return (write(1, &letter[ind], length) + write(1, &letter[0], i));
		}
		else
		{
			return (write(1, &letter[0], i) + write(1, &letter[ind], length));
		}
	}

	return (write(1, &letter[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @letter: Arrays of chars
 * @ind: Index at which the number starts in the letter
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @space: Char representing the padding
 * @extra_c: Char representing extra char
 * @space_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int writef_pointer(char letter[], int ind, int length,
	int width, int flags, char space, char extra_c, int space_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			letter[i] = space;
		letter[i] = '\0';
		if (flags & PRINTF_MINUS && space == ' ')
		{
			letter[--ind] = 'x';
			letter[--ind] = '0';
			if (extra_c)
				letter[--ind] = extra_c;
			return (write(1, &letter[ind], length) + write(1, &letter[3], i - 3));
		}
		else if (!(flags & PRINTF_MINUS) && space == ' ')
		{
			letter[--ind] = 'x';
			letter[--ind] = '0';
			if (extra_c)
				letter[--ind] = extra_c;
			return (write(1, &letter[3], i - 3) + write(1, &letter[ind], length));
		}
		else if (!(flags & PRINTF_MINUS) && space == '0')
		{
			if (extra_c)
				letter[--space_start] = extra_c;
			letter[1] = '0';
			letter[2] = 'x';
			return (write(1, &letter[space_start], i - space_start) +
				write(1, &letter[ind], length - (1 - space_start) - 2));
		}
	}
	letter[--ind] = 'x';
	letter[--ind] = '0';
	if (extra_c)
		letter[--ind] = extra_c;
	return (write(1, &letter[ind], BUFFER_SIZE - ind - 1));
}
