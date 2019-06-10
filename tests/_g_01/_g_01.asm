global _main

extern _printf                ; Uncomment under Windows

section .data
        fmtStr:  db 'hello, world',0xA,0

section .text
        _main:

        push 5

        loop1:

        sub     esp, 4          ; Allocate space on the stack for one 4 byte parameter

        lea     eax, [fmtStr]
        mov     [esp], eax      ; Arg1: pointer to format string
        call    _printf         ; Call printf(3):
                                ;       int printf(const char *format, ...);

        add     esp, 4          ; Pop stack once

        pop ecx
        dec ecx
        push ecx
        jne loop1

        pop ecx

        ret