global _start

extern _ExitProcess@4

section .text

        _start:
        mov ecx,555
        push    dword 0         ; Arg1: push exit code
        call    _ExitProcess@4
        