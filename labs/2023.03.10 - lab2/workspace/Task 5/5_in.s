	.file	"5_in.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%llu"
.LC1:
	.string	"Correct!"
.LC2:
	.string	"Wrong"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	eax, 3735929054
	mov	QWORD PTR -16[rbp], rax
	lea	rax, -24[rbp]
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	mov	rax, QWORD PTR -24[rbp]
	xor	rax, 322423550
	mov	QWORD PTR -24[rbp], rax
	mov	rax, QWORD PTR -24[rbp]
	cmp	QWORD PTR -16[rbp], rax
	jne	.L2
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	puts@PLT
	jmp	.L3
.L2:
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	puts@PLT
.L3:
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
