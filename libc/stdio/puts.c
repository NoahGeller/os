#include <stdio.h>

int puts(const char* restrict str) {
	return printf("%s\n", str);
}
