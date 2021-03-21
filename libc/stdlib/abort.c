#include <stdlib.h>
#include <stdio.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
	// TODO: Add a proper kernel panic.
	printf("KERNEL: PANIC: abort()\n");
#else
	// TODO: Abnormally terminate the process.
	printf("abort()\n");
#endif
	while (1) { }
	__builtin_unreachable();
}
