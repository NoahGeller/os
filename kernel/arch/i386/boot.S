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

.section .text
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
