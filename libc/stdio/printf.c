#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ASCII_DEC_BASE 		48
#define ASCII_HEX_LC_BASE	97

static bool print(const char* data, size_t len) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < len; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

static size_t dec_len(int number) {
	size_t len = 1;
	int n = number;
	while (n / 10 != 0) {
		len++;
		n /= 10;
	}
	return len;
}

static bool dec_print(int number) {
	size_t len = dec_len(number);
	char str[len];
	int n = number;
	for (size_t i = 0; i < len; i++) {
		int digit = n % 10;
		n /= 10;
		str[len - i - 1] = ASCII_DEC_BASE + digit;
	}
	return print(str, len);
}

static size_t hex_len(unsigned int number) {
	size_t len = 3;
	unsigned int x = number;
	while (x / 16 != 0) {
		len++;
		x /= 16;
	}
	return len;
}

static bool hex_print(unsigned int number) {
	size_t len = hex_len(number);
	char str[len];
	str[0] = '0';
	str[1] = 'x';
	unsigned int x = number;
	for (size_t i = len - 1; i > 1; i--) {
		unsigned int digit = x % 16;
		x /= 16;
		if (digit <= 9)
			str[i] = ASCII_DEC_BASE + digit;
		else
			str[i] = ASCII_HEX_LC_BASE + digit - 10;
	}
	return print(str, len);
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd' || *format == 'i') {
			format++;
			int n = va_arg(parameters, int);
			size_t len = dec_len(n);
			if(maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!dec_print(n))
				return -1;
			written += len;
		} else if (*format == 'x') {
			format++;
			int x = va_arg(parameters, int);
			size_t len = hex_len(x);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!hex_print(x))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
