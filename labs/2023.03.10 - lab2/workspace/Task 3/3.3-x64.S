.intel_syntax noprefix
.text
    .global main

myst5:
    xor eax, eax
    cmp rdi, 1
    jbe .L1
    cmp rdi, 3
    jbe .L6
    test dil, 1
    je .L1
    mov ecx, 2
    jmp .L3
.L4:
    mov rax, rdi
    xor edx, edx
    div rcx
    test rdx, rdx
    je .L8
.L3:
    add rcx, 1
    mov rax, rcx
    imul rax, rcx
    cmp rax, rdi
    jbe .L4
.L6:
    mov eax, 1
    ret
.L8:
    xor eax, eax
.L1:
    ret

main:
    # Function prologue
    push rbp
    mov rbp, rsp


    mov rbx, 0
for:
    # Call myst5()
    mov rdi, rbx
    call myst5

    # Print result
    lea rdi, [rip + main_format]
    mov rsi, rbx
    mov rdx, rax
    call printf

    add rbx, 1

    cmp rbx, 50
    jle for


    # Return zero
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
main_format:
    .string "result[%llu] = %llu\n"
