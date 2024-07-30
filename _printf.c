#include "main.h"

/**
 * print_number - prints an integer
 * @n: integer to be printed
 *
 * Return: the number of characters printed
 */
int print_number(int n)
{
	int count = 0;
	unsigned int num;

	if (n < 0)
	{
		count += write(1, "-", 1);
		num = -n;
	}
	else
	{
		num = n;
	}
	if (num / 10)
		count += print_number(num / 10);
	count += write(1, &("0123456789"[num % 10]), 1);
	return (count);
}

/**
 * handle_specifier - handles format specifiers
 * @format: format specifier character
 * @args: argument list
 *
 * Return: the number of characters printed
 */
int handle_specifier(char format, va_list args)
{
	int count = 0;
	char c, *str;

	if (format == 'c')
	{
		c = va_arg(args, int);
		count += write(1, &c, 1);
	}
	else if (format == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
			str = "(null)";
		while (*str)
			count += write(1, str++, 1);
	}
	else if (format == 'd' || format == 'i')
	{
		count += print_number(va_arg(args, int));
	}
	else if (format == '%')
	{
		count += write(1, "%", 1);
	}
	return (count);
}

/**
 * _printf - produces output according to a format
 * @format: character string containing zero or more directives
 *
 * Return: the number of characters printed (excluding the null byte
 * used to end output to strings)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);
	while (format && *format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_specifier(*format, args);
		}
		else
		{
			count += write(1, format, 1);
		}
		format++;
	}
	va_end(args);
	return (count);
}

