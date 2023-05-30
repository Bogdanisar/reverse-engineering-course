.intel_syntax noprefix
.text
    .global main

.LC1:
    lea	rax, 0x0D0D0D0D[rax]

main:
    ret
