.intel_syntax noprefix
.text
    .global main


my_function:
    movabs rdx, -1085102592571150095
    mov rax, rdi
    mul rdx
    mov rax, rdx
    shr rax, 4
    ret


main:
    # Function prologue
    push rbp
    mov rbp, rsp


    mov rbx, 0
for:
    # Call function
    mov rdi, rbx
    call my_function

    # Print result
    lea rdi, [rip + main_format]
    mov rsi, rbx
    mov rdx, rax
    call printf

    add rbx, 1

    cmp rbx, 100
    jle for


    # Return zero
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret
main_format:
    .string "result[%llu] = %llu\n"
