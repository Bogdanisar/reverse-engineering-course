add:
        test    edi, edi
        jle     .L4
        add     edi, 1
        mov     eax, 1
        mov     edx, 0
.L3:
        add     edx, eax
        add     eax, 1
        cmp     eax, edi
        jne     .L3
.L1:
        mov     eax, edx
        ret
.L4:
        mov     edx, 0
        jmp     .L1
