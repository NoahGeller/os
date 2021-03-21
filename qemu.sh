#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-arch.sh $HOST) -cdrom os.iso
