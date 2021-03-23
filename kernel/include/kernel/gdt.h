/* @file tty.h */
#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>
#include <stddef.h>

#define GDT_CODE_SELECTOR	0x08

struct GDTEntry {
	uint32_t base;
	uint32_t limit;
	char type;
};

struct GDTDescriptor {
	uint8_t size;
	uint32_t offset;
};

/**
 * Loads a Global Descriptor Table.
 * @param[in] GDT Pointer to the start of a GDT.
 * @param[in] size Size of the GDT.
 */
extern void load_gdt(uint64_t* GDT, size_t size);

/**
 * Loads a GDT with entirely overlapping segments, effectively disabling
 * segmentation.
 *
 * On x86, memory is initially laid out in segments with different attributes
 * and privilege levels. If we want to enable paging later, we have to find a
 * way to disable this segmentation effect. In order to do so, we load a new
 * GDT that maps all segments to the same 4 GiB, which is fully readable and
 * writeable, as though the segmentation never happened in the first place.
 */
void gdt_init(void);

#endif
