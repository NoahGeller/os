/* @file gdt.c */
#include <kernel/gdt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Each entry is 8 bytes, so we declare an array of 8-byte ints as our GDT.
extern uint64_t GDT[4];
uint64_t GDT[4];

void encode_gdt_entry(uint8_t* target, struct GDTEntry src) {
	// Make sure that the limit is encodable.
	if ((src.limit > 65536) && ((src.limit & 0xfff) != 0xfff)) {
		puts("KERNEL: GDT entry limit is too large!");
		abort();
	}

	// Adjust granularity if necessary.
	if (src.limit > 65536) {
		src.limit = src.limit >> 12;
		target[6] = 0xc0;
	} else {
		target[6] = 0x40;
	}

	// Encode the limit.
	target[0] = src.limit & 0xff;
	target[1] = (src.limit >> 8) & 0xff;
	target[6] |= (src.limit >> 16) & 0xf;

	// Encode the base.
	target[2] = src.base & 0xff;
	target[3] = (src.base >> 8) & 0xff;
	target[4] = (src.base >> 16) & 0xff;
	target[7] = (src.base >> 24) & 0xff;

	// Encode the type.
	target[5] = src.type;
}

void disable_segmentation(void) {
	const struct GDTEntry null_entry = {
		.base = 0,
		.limit = 0,
		.type = 0
	};

	const struct GDTEntry code = {
		.base = 0,
		.limit = 0xffffffff,
		.type = 0x9a
	};

	const struct GDTEntry data = {
		.base = 0,
		.limit = 0xffffffff,
		.type = 0x92
	};

	encode_gdt_entry((uint8_t*) &GDT[0], null_entry);
	encode_gdt_entry((uint8_t*) &GDT[1], code);
	encode_gdt_entry((uint8_t*) &GDT[2], data);

	load_gdt(&GDT[0], sizeof(GDT));
}
