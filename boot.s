section .multiboot
align 4 ; grub needs it to be aligned to four bytes
    dd 0x1BADB002 ; Magic
    dd 0x00 ; 0x00 for a minimal setup
    dd -(0x1BADB002 + 0x00) ; Checksum: magic + flags + checksum == 0, ensures header isn't corrupted

section .text ; here lies executable code
global _start ; entry point
extern kernel_main ; kernel main exists in C code

_start: ; grub go here after loading kernel
    call kernel_main ; push address onto stack (ESP = return address) + jump to kernel_main
    cli ; disables hardware interrupts because at this point in time interrupt handlers don't exist here yet
.hang: ; infinite halt loop
    hlt ; CPU sleeps until next interrupt
    jmp .hang ; Infinite loop