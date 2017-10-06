.section multiboot
.align 4
.long 0x1BADB002
.long 0x3
.long -(0x1BADB002 + 0x3)

.section bootstrap_text, "ax"
.global _start
.type _start, @function
_start:
	# Add the page tables to the page directory
    movl $(pageTableBootstrap + 0x3), kernelPageDirectory
    movl $(pageTableKernel + 0x3), kernelPageDirectory + 0xC00
	movl $(pageTablePhysicalMemory + 0x3), kernelPageDirectory + 0xFF8

	# Recursively map the page directory at 0xFFC00000
	movl $(kernelPageDirectory + 0x3), kernelPageDirectory + 0xFFC

    # Identity-map the bootstrap section
    mov $numBootstrapPages, %ecx
    mov $(pageTableBootstrap + 256 * 4), %edi
    mov $(bootstrapBegin + 3), %edx

1:  mov %edx, (%edi)
    add $4, %edi
    add $0x1000, %edx
    loop 1b

    # Map the kernel
    mov $numKernelPages, %ecx
    add $(pageTableKernel - pageTableBootstrap), %edi
    mov $(kernelPhysicalBegin + 3), %edx

1:  mov %edx, (%edi)
    add $4, %edi
    add $0x1000, %edx
    loop 1b

    # Map video memory at 0xC0000000.
    movl $0xB8003, pageTableKernel

    # Enable paging
    mov $kernelPageDirectory, %ecx
    mov %ecx, %cr3

    mov %cr0, %ecx
    or $0x80000000, %ecx
    mov %ecx, %cr0

    # Jump into the higher half
    jmp _start2
.size _start, . - _start

.section bootstrap_bss, "aw", @nobits
.align 4096
.global kernelPageDirectory
kernelPageDirectory:
    .skip 4096
pageTableBootstrap:
    .skip 4096
pageTableKernel:
    .skip 4096
pageTablePhysicalMemory:
	.skip 4096

.section .text
.type _start2, @function
_start2:
	# load the GDT
	mov $gdt_descriptor, %ecx
	lgdt (%ecx)
	mov $0x10, %cx
	mov %cx, %ds
	mov %cx, %es
	mov %cx, %fs
	mov %cx, %gs
	mov %cx, %ss
	ljmp $0x8, $1f

	# load the IDT
1:	mov $idt_descriptor, %ecx
	lidt (%ecx)
	
	mov $kernel_stack, %esp

	push $0
	push $0
	mov %esp, %ebp

	push %ebx
	push %eax

	call _init
	call kernel_main

_halt:
	cli
	hlt
	jmp _halt
.size _start2, . - _start2

.section .bss
.align 4096
.skip 4096

kernel_stack:
