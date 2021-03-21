#include <kernel/tty.h>
#include <stdio.h>
#include <stdlib.h>

void kmain(void) {
	terminal_initialize();
	puts("Hello, world!");
}
