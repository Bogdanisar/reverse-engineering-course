.intel_syntax noprefix
.text
    .global main

myst4:
    push rbp
    push rbx
    sub rsp, 8
    mov rbx, rdi
    cmp rdi, 1
    ja .L4
.L2:
    mov rax, rbx
    add rsp, 8
    pop rbx
    pop rbp
    ret
.L4:
    lea rdi, [rdi-1]
    call myst4
    mov rbp, rax
    lea rdi, [rbx-2]
    call myst4
    lea rbx, [rbp+0+rax]
    jmp .L2

main:
    # Function prologue
    push rbp
    mov rbp, rsp

    # Call myst4()
    mov rdi, 8
    call myst4

    # Print result
    lea rdi, [rip + main_format]
    mov rsi, rax
    call printf

    # Return zero
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
main_format:
    .string "result = %llu\n"
