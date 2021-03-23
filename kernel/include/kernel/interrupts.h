/* @file interrupts.h */
#include <stdint.h>
#include <stddef.h>

#define IDT_PRESENT		0b10000000
#define IDT_USER		0b01100000

#define IDT_INTERRUPT	0xe
#define IDT_TRAP		0xf

struct IDTEntry {
	uint32_t offset;
	uint16_t selector;
	uint8_t type_attr;
};

struct IDT {
	uint64_t divide_error;
	uint64_t debug;
	uint64_t nmi;
	uint64_t breakpoint;
	uint64_t overflow;
	uint64_t bound_range_exceeded;
	uint64_t invalid_opcode;
	uint64_t device_not_available;
	uint64_t double_fault;
	uint64_t coprocessor_segment_overrun;
	uint64_t invalid_tss;
	uint64_t segment_not_present;
	uint64_t general_protection;
	uint64_t page_fault;
};

void idt_init(void);

/**
 * Loads an Interrupt Descriptor Table.
 * @param[in] IDT Pointer to the start of an IDT.
 * @param[in] size Size of the IDT.
 */
extern void load_idt(uint64_t* IDT, size_t size);
