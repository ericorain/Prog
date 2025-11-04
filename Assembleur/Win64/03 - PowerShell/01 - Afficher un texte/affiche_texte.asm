DEFAULT REL

global main

extern printf
extern ExitProcess

section .data
    message:
        db   "Bonjour", 10, 0

section .text
    main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32

        lea     rcx, [message]
        call    printf

        call    ExitProcess