BITS 64
DEFAULT REL
                                                ; Message Box, 64 bit. V1.02
MB_OK         EQU 0                             ; Constants

extern MessageBoxA                              ; Import external symbols
extern ExitProcess                              ; Windows API functions, not decorated

global WinMain                                  ; Export symbols. The entry point

section .data                                   ; Initialized data segment
MessageBoxText    db "Bonjour", 0
MessageBoxCaption db "MessageBox 64", 0

section .text                                   ; Code segment

WinMain:

sub   RSP, 8                                   ; Align the stack to a multiple of 16 bytes
sub   RSP, 32                                  ; 32 bytes of shadow space

xor   ECX, ECX                                 ; 1st parameter
lea   RDX, [MessageBoxText]                    ; 2nd parameter
lea   R8, [MessageBoxCaption]                  ; 3rd parameter
mov   R9D, MB_OK                               ; 4th parameter
call  MessageBoxA

add   RSP, 32                                  ; Remove the 32 bytes

xor   ECX, ECX
call  ExitProcess