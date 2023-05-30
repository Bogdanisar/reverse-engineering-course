add:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-20], edi
        mov     DWORD PTR [rbp-4], 0
        mov     DWORD PTR [rbp-8], 1
        jmp     .L2
.L3:
        mov     eax, DWORD PTR [rbp-8]
        add     DWORD PTR [rbp-4], eax
        add     DWORD PTR [rbp-8], 1
.L2:
        mov     eax, DWORD PTR [rbp-8]
        cmp     eax, DWORD PTR [rbp-20]
        jle     .L3
        mov     eax, DWORD PTR [rbp-4]
        pop     rbp
        ret
