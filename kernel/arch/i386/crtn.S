.section .init
	/* GCC will place the contents of crtend.o's .init section here. */
	popl %ebp
	ret

.section .fini
	/* GCC will place the contents of crtend.o's .fini section here. */
	popl %ebp
	ret
