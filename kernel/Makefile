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
BOOTDIR ?= $(EXEC_PREFIX)/boot
HEADERS ?= $(PREFIX)/include

CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -lk -lgcc

ARCHDIR = arch/$(ARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS =\
	$(KERNEL_ARCH_OBJS) \
	kernel/kernel.o \

OBJS =\
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o \

LINK_SCRIPT = $(ARCHDIR)/linker.ld

LINK_LIST =\
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJS) \
	$(LIBS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o \

KERNEL = os.kernel

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: $(KERNEL)

$(KERNEL): $(OBJS) $(LINK_SCRIPT)
	$(CC) -T $(LINK_SCRIPT) -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $(KERNEL)

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(KERNEL)
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: $(KERNEL)
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(KERNEL) $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
