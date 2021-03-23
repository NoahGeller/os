/* @file interrupts.c */
#include <kernel/interrupts.h>
#include <kernel/gdt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct IDT IDT;

void encode_idt_entry(uint64_t* target, const struct IDTEntry* src) {
	uint8_t* target_bytes = (uint8_t*) target;

	// Encode the offset.
	target_bytes[0] = src->offset & 0xff;
	target_bytes[1] = (src->offset >> 8) & 0xff;
	target_bytes[6] = (src->offset >> 16) & 0xff;
	target_bytes[7] = (src->offset >> 24) & 0xff;

	// Encode the selector.
	target_bytes[2] = src->selector & 0xff;
	target_bytes[3] = (src->selector >> 8) & 0xff;

	// Encode the type and attributes.
	target_bytes[5] = src->type_attr;

	// Fill in the reserved space.
	target_bytes[4] = 0;
}

void handle_double_fault(void) {
	puts("Double fault!");
	abort();
}

void idt_init(void) {
	const struct IDTEntry missing = {
		.offset = 0,
		.selector = GDT_CODE_SELECTOR,
		.type_attr = IDT_INTERRUPT
	};

	for (size_t i = 0; i < 3; i++) {
		encode_idt_entry((uint64_t*) &IDT + i, &missing);
	}

	const struct IDTEntry double_fault = {
		.offset = (uint32_t) &handle_double_fault,
		.selector = GDT_CODE_SELECTOR,
		.type_attr = IDT_PRESENT | IDT_INTERRUPT
	};

	encode_idt_entry(&(IDT.double_fault), &double_fault);

	load_idt((uint64_t*) &IDT, sizeof(IDT));
}
