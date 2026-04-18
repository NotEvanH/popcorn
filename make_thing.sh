# Build Commands
nasm -f elf32 boot.s -o boot.o
gcc -m32 -c kernel.c -o kernel.o -ffreestanding
ld -m elf_i386 -T linker.ld -o kernel.elf boot.o kernel.o

# Create Bootable ISO
mkdir -p iso/boot/grub
cp kernel.elf iso/boot
cp boot/grub/grub.cfg iso/boot/grub
grub-mkrescue -o testos.iso iso

# Run It
qemu-system-i386 -cdrom testos.iso