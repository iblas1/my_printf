#include "main.h"

/**
 * is_printablef - Evaluates if a char is printable
 * @d: Char to be evaluated.
 *
 * Return: 1 if d is printable, 0 otherwise
 */
int is_printablef(char d)
{
	if (d >= 32 && d < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_codef - Append ascci in hexadecimal code to letter
 * @letter: Array of chars.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_codef(char ascii_code, char letter[], int i)
{
	char put_in[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	letter[i++] = '\\';
	letter[i++] = 'x';

	letter[i++] = put_in[ascii_code / 16];
	letter[i] = put_in[ascii_code % 16];

	return (3);
}

/**
 * is_digitf - Verifies if a char is a digit
 * @d: Char to be evaluated
 *
 * Return: 1 if d is a digit, 0 otherwise
 */
int is_digitf(char d)
{
	if (d >= '0' && d <= '9')
		return (1);

	return (0);
}

/**
 * convert_number_size - Casts a number to the specified letter_size
 * @number: Number to be casted.
 * @letter_size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_number_size(long int number, int letter_size)
{
	if (letter_size == PRINTS_LONG)
		return (number);
	else if (letter_size == PRINTS_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_unsigned_size - Casts a number to the specified letter_size
 * @number: Number to be casted
 * @letter_size: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convert_unsigned_size(unsigned long int number, int letter_size)
{
	if (letter_size == PRINTS_LONG)
		return (number);
	else if (letter_size == PRINTS_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
