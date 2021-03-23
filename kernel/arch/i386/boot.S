/* Constants for the multiboot header. */
.set ALIGN,		1 << 0				/* align loaded modules on page boundaries */
.set MEMINFO,	1 << 1				/* provide memory map */
.set FLAGS,		ALIGN | MEMINFO
.set MAGIC,		0x1badb002			/* identifies header as such */
.set CHECKSUM,	-(MAGIC + FLAGS)

/* Multiboot header. */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss

/* Create a small stack. */
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .data

/* This record will hold the size and offset of the GDT. */
gdtr:
.short 0
.long 0

/* This record will hold the size and offset of the IDT. */
idtr:
.short 0
.long 0

.section .text

.global load_gdt
.type load_gdt, @function
load_gdt:
	/* ESP+4 contains the address of the GDT. */
	movl 4(%esp), %eax
	movl %eax, gdtr + 2
	/* ESP+8 contains the size of the GDT. */
	movw 8(%esp), %ax
	sub 1, %ax
	movw %ax, gdtr
	/* Load the GDT using the newly populated record. */
	lgdt gdtr
	/* Update the new CS register and continue the flush. */
	jmp $0x08, $flush_gdt

/* Update all of the data registers. */
flush_gdt:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret

.size load_gdt, . - load_gdt

.global load_idt
.type load_idt, @function
load_idt:
	/* ESP+4 contains the address of the IDT. */
	movl 4(%esp), %eax
	movl %eax, idtr + 2
	/* ESP+8 contains the size of the IDT. */
	movw 8(%esp), %ax
	sub 1, %ax
	movw %ax, idtr
	/* Load the IDT using the newly populated record. */
	lidt idtr
	ret

.global _start
.type _start, @function
_start:
	/* Initialize the stack. */
	mov $stack_top, %esp

	/* Drop into our main kernel code. */
	call kmain

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
