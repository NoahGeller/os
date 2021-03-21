DEFAULT_HOST != ../default-host.sh
HOST := $(DEFAULT_HOST)
ARCH != ../target-arch.sh $(HOST)

# Default flags (non-project-specific).
CFLAGS ?= -O2 -g
LDFLAGS ?=
LIBS ?=

DESTDIR ?=
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
INCLUDEDIR ?= $(EXEC_PREFIX)/include
LIBDIR ?= $(EXEC_PREFIX)/lib

CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra
LIBK_CFLAGS := $(CFLAGS)

ARCHDIR = arch/$(ARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(ARCH_CFLAGS) -D__is_libc
LIBK_CFLAGS := $(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS) -D__is_libk

FREEOBJS =\
	$(ARCH_FREEOBJS) \
	stdlib/abort.o \
	stdio/putchar.o \
	stdio/printf.o \
	stdio/puts.o \
	string/strlen.o \

HOSTEDOBJS =\
	$(ARCH_HOSTEDOBJS) \

OBJS =\
	$(FREEOBJS) \
	$(HOSTEDOBJS) \

LIBK_OBJS = $(FREEOBJS:.o=.libk.o)

BINARIES = libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS)

clean:
	rm -f $(BINARIES)
	rm -f $(OBJS) $(LIBK_OBJS)
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d)

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)

-include $(LIBK_OBJS:.o=.d)
