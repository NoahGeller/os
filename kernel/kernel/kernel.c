/* @file kernel.c */
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <stdio.h>
#include <stdlib.h>

void kmain(void) {
	terminal_init();
	puts("Hello, world!\n");

	puts("Disabling segmentation...");
	disable_segmentation();
	puts("Segmentation disabled!");
}
