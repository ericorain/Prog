# 1 - Description

Affiche un texte sous PowerShell en assembleur Win64 avec NASM et GCC.

# 2 - Code

affiche_texte.asm
``` asm
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
```

# 3 - Compilation

```
nasm -f win64 affiche_texte.asm
gcc -o affiche_texte.exe affiche_texte.obj
```

``` powershell
D:\data\git\programming\asm\nasm\MessageBox>nasm -f win64 affiche_texte.asm

D:\data\git\programming\asm\nasm\MessageBox>gcc -o affiche_texte.exe affiche_texte.obj

D:\data\git\programming\asm\nasm\MessageBox>dir affiche_texte.*
 Le volume dans le lecteur D n’a pas de nom.
 Le numéro de série du volume est 0C0C-BE1F

 Répertoire de D:\data\git\programming\asm\nasm\MessageBox

02/11/2025  21:10               314 affiche_texte.asm
02/11/2025  21:17            53 045 affiche_texte.exe
02/11/2025  21:17               378 affiche_texte.obj
               3 fichier(s)           53 737 octets
               0 Rép(s)  3 062 192 238 592 octets libres

D:\data\git\programming\asm\nasm\MessageBox>
```

# 4 - Exécution

Affiche un texte.

``` powershell
D:\data\git\programming\asm\nasm\MessageBox>affiche_texte.exe
Bonjour

D:\data\git\programming\asm\nasm\MessageBox>
```