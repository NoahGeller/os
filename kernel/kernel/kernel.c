/* @file kernel.c */
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <stdio.h>
#include <stdlib.h>

void kmain(void) {
	terminal_init();
	puts("Hello, world!\n");

	printf("Initializing GDT...");
	gdt_init();
	printf("success!\n\n");

	printf("Loading interrupts...");
	idt_init();
	printf("success!\n\n");
}
