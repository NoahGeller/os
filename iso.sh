#!/bin/sh
set -e
. ./build.sh

mkdir -p iso
mkdir -p iso/boot
mkdir -p iso/boot/grub

cp $SYSROOT$BOOTDIR/os.kernel iso/boot/os.kernel
cat > iso/boot/grub/grub.cfg << EOF
set timeout=0
set default=0
menuentry "os" {
	multiboot /boot/os.kernel
	boot
}
EOF

grub-mkrescue -o os.iso iso
