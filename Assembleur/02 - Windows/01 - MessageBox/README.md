# 1 - Description

Création d'une popup simple sous Windows en assembleur Win64 avec NASM et GCC.

# 2 - Code

messagebox.asm
``` asm
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
```

# 3 - Compilation

```
nasm -f win64 messagebox.asm
gcc -mwindows -o messagebox.exe messagebox.obj
```

``` powershell
d:\Prog\Assembleur\02 - Windows\01 - MessageBox>nasm -f win64 messagebox.asm

d:\Prog\Assembleur\02 - Windows\01 - MessageBox>gcc -mwindows -o messagebox.exe messagebox.obj

d:\Prog\Assembleur\02 - Windows\01 - MessageBox>dir messagebox.*
 Le volume dans le lecteur D n’a pas de nom.
 Le numéro de série du volume est 0C0C-BE1F

 Répertoire de d:\Prog\Assembleur\02 - Windows\01 - MessageBox

02/11/2025  22:07             1 196 messagebox.asm
02/11/2025  22:07            55 190 messagebox.exe
02/11/2025  22:07               503 messagebox.obj
               3 fichier(s)           56 889 octets
               0 Rép(s)  3 062 191 120 384 octets libres

d:\Prog\Assembleur\02 - Windows\01 - MessageBox>
```

Note : le paramètre "-mwindows" permet de supprimer une fenêtre de console intempestive qui reste affichée à l'écran tant que la popup est affichée.

# 4 - Exécution

Une popup est affichée avec un bouton "OK".

``` powershell
d:\Prog\Assembleur\02 - Windows\01 - MessageBox>messagebox.exe

d:\Prog\Assembleur\02 - Windows\01 - MessageBox>
```