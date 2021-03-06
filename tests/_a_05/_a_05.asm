global _start

extern _GetStdHandle@4
extern _WriteConsoleA@20
extern _ExitProcess@4

section .data
        str:     db 'path 1',0x0D,0x0A
        strLen:  equ $-str
        str2:    db 'path 2',0x0D,0x0A
        strLen2: equ $-str2

section .bss
        numCharsWritten:        resd 1

section .text

        _func1:
                ;
        ; HANDLE WINAPI GetStdHandle( _In_  DWORD nStdHandle ) ;
        ;
        push    dword -11       ; Arg1: request handle for standard output
        call    _GetStdHandle@4 ; Result: in eax

        ; BOOL WINAPI WriteConsole(
        ;       _In_        HANDLE hConsoleOutput,
        ;       _In_        const VOID *lpBuffer,
        ;       _In_        DWORD nNumberOfCharsToWrite,
        ;       _Out_       LPDWORD lpNumberOfCharsWritten,
        ;       _Reserved_  LPVOID lpReserved ) ;
        ;
        push    dword 0         ; Arg5: Unused so just use zero
        push    numCharsWritten ; Arg4: push pointer to numCharsWritten
        push    dword strLen    ; Arg3: push length of output string
        push    str             ; Arg2: push pointer to output string
        push    eax             ; Arg1: push handle returned from _GetStdHandle
        call    _WriteConsoleA@20
        ret

        _func2:
        call _func1
        
        ;
        ; HANDLE WINAPI GetStdHandle( _In_  DWORD nStdHandle ) ;
        ;
        push    dword -11       ; Arg1: request handle for standard output
        call    _GetStdHandle@4 ; Result: in eax

        ; BOOL WINAPI WriteConsole(
        ;       _In_        HANDLE hConsoleOutput,
        ;       _In_        const VOID *lpBuffer,
        ;       _In_        DWORD nNumberOfCharsToWrite,
        ;       _Out_       LPDWORD lpNumberOfCharsWritten,
        ;       _Reserved_  LPVOID lpReserved ) ;
        ;
        push    dword 0         ; Arg5: Unused so just use zero
        push    numCharsWritten ; Arg4: push pointer to numCharsWritten
        push    dword strLen2   ; Arg3: push length of output string
        push    str2            ; Arg2: push pointer to output string
        push    eax             ; Arg1: push handle returned from _GetStdHandle
        call    _WriteConsoleA@20
        ret

        _start:

        push 5
        mov ebx,3

        call _func1

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


        push    dword 0         ; Arg1: push exit code
        call    _ExitProcess@4
        