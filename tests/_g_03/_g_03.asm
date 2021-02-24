global _main

extern _printf                ; Uncomment under Windows

section .data
        fmtStr:  db '1',0xA,0
        fmtStr2: db '2',0xA,0

section .text
		_func1:
		sub     esp, 4          ; Allocate space on the stack for one 4 byte parameter
        lea     eax, [fmtStr]
        mov     [esp], eax      ; Arg1: pointer to format string
        call    _printf         ; Call printf(3):
                                ;       int printf(const char *format, ...);
        add     esp, 4          ; Pop stack once
        ret
        
		_func2:
		call _func1
		sub     esp, 4          ; Allocate space on the stack for one 4 byte parameter
        lea     eax, [fmtStr2]
        mov     [esp], eax      ; Arg1: pointer to format string
        call    _printf         ; Call printf(3):
                                ;       int printf(const char *format, ...);
        add     esp, 4          ; Pop stack once
        ret

        _main:

        push 5
        mov ebx,3
        loop1:

        dec ebx
        jnz else

        call _func1

        else:

        call _func2

        pop ecx
        dec ecx
        push ecx
        jne loop1
        pop ecx

        ret