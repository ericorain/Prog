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
gcc -nostartfiles -o affiche_texte.exe affiche_texte.obj
```

``` powershell
d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte>nasm -f win64 affiche_texte.asm

d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte>gcc -nostartfiles -o affiche_texte.exe affiche_texte.obj

d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte>dir affiche_texte.*
 Le volume dans le lecteur D n’a pas de nom.
 Le numéro de série du volume est 0C0C-BE1F

 Répertoire de d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte

02/11/2025  21:10               314 affiche_texte.asm
03/11/2025  11:20             8 336 affiche_texte.exe
03/11/2025  11:20               378 affiche_texte.obj
               3 fichier(s)            9 028 octets
               0 Rép(s)  3 062 190 456 832 octets libres

d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte>
```

Note : avec le paramètre "-nostartfiles", le linkeur ne se sert pas des fichiers de démarrage système standard lors de l'édition de liens. Les bibliothèques système standard sont utilisées normalement, sauf si les options -nostdlib, -nolibc ou -nodefaultlibs sont utilisées. Ici, on gagne presque 50 Ko et le programme devient plus petit.

# 4 - Exécution

Affiche un texte.

``` powershell
d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte>affiche_texte.exe
Bonjour

d:\Prog\Assembleur\03 - PowerShell\01 - Afficher un texte>
```