# 1 - Description

Création d'une fenêtre DialogBoxParam sous Windows en assembleur Win64 avec NASM et GCC.

# 2 - Code

dialogoxparam.asm
``` asm
BITS 64
DEFAULT REL

; Constantes
CS_HREDRAW EQU 2
CS_VREDRAW EQU 1
NULL EQU 0
DLGWINDOWEXTRA EQU 30
COLOR_BTNFACE EQU 15
IDI_APPLICATION EQU 7F00h
IDC_ARROW EQU 7F00h
SW_SHOWNORMAL EQU 1
WM_COMMAND EQU 111h ;0x0111
WM_DESTROY EQU 2
BN_CLICKED EQU 0
IDC_BUTTONOK EQU 1004
IDC_BUTTONCANCEL EQU 1005
IDC_DIALOG	equ 200
WM_CLOSE EQU 10h


; Importation des fonctions de Windows
extern GetModuleHandleA
extern LoadIconA
extern LoadCursorA
extern RegisterClassExA
extern CreateDialogParamA
extern ShowWindow
extern UpdateWindow
extern GetMessageA
extern IsDialogMessageA
extern TranslateMessage
extern DispatchMessageA
extern DefWindowProcA
extern PostQuitMessage
extern SendMessageA
extern ExitProcess

; Macros

; /* Pour WinMain */
; wc
%define wc                 RBP - 136            ; WNDCLASSEX structure, 80 bytes
%define wc.cbSize          RBP - 136            ; 4 bytes. Start on an 8 byte boundary
%define wc.style           RBP - 132            ; 4 bytes
%define wc.lpfnWndProc     RBP - 128            ; 8 bytes
%define wc.cbClsExtra      RBP - 120            ; 4 bytes
%define wc.cbWndExtra      RBP - 116            ; 4 bytes
%define wc.hInstance       RBP - 112            ; 8 bytes
%define wc.hIcon           RBP - 104            ; 8 bytes
%define wc.hCursor         RBP - 96             ; 8 bytes
%define wc.hbrBackground   RBP - 88             ; 8 bytes
%define wc.lpszMenuName    RBP - 80             ; 8 bytes
%define wc.lpszClassName   RBP - 72             ; 8 bytes
%define wc.hIconSm         RBP - 64             ; 8 bytes. End on an 8 byte boundary

; msg
%define msg                RBP - 56             ; MSG structure, 48 bytes
%define msg.hwnd           RBP - 56             ; 8 bytes. Start on an 8 byte boundary
%define msg.message        RBP - 48             ; 4 bytes
%define msg.Padding1       RBP - 44             ; 4 bytes. Natural alignment padding
%define msg.wParam         RBP - 40             ; 8 bytes
%define msg.lParam         RBP - 32             ; 8 bytes
%define msg.time           RBP - 24             ; 4 bytes
%define msg.py.x           RBP - 20             ; 4 bytes
%define msg.pt.y           RBP - 16             ; 4 bytes
%define msg.Padding2       RBP - 12             ; 4 bytes. Structure length padding

%define hDlg               RBP - 8              ; 8 bytes

; /* Pour WndProc */
%define hWnd   RBP + 16                         ; Location of the shadow space setup by
%define uMsg   RBP + 24                         ; the calling function
%define wParam RBP + 32
%define lParam RBP + 40

; Point d'entrée
global start

; Données
section .data
ClassName db "ClasseDLG",0

; Données non initialisées
section .bss
alignb 8
hInstance resq 1

; Début du code
section .text
start:

    ; Alignement du pointeur de la pile sur 16 octets
    sub rsp,8

    ; 32 octets de shadow space avant l'appel d'une fonction Windows
    sub rsp,32

    ; Récupération d'un handle de module 
    xor rcx,rcx
    call GetModuleHandleA
    mov qword [hInstance],rax

    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Appel de la fonction WinMain
    call WinMain

    ; Fin du programme
    xor rcx,rcx
    call ExitProcess


; Fonction principal
WinMain:

    ; Sauvegarde du registre rbp qui sera utilisé pour l'accès aux données sur la pile
    push rbp
    ; Sauvegarde du pointeur de la pile qui sera restauré à la fin de la fonction
    mov rbp,rsp

    ; Allocation de 136 octets sur la pile pour les variables locales (wc, msg et hDlg)
    ; 136 n'étant pas un multiple de 16 octets (obligatoire pour les appels aux fonctions Windows),
    ; 8 octets sont donc ajoutés (ce qui fait 144 octets c'est-à-dire 9 x 16 octets)
    sub rsp,136 + 8

    ; Initialisation des données de la structure wc
    mov dword [wc.cbSize],80
    mov dword [wc.style],CS_HREDRAW | CS_VREDRAW
    lea rax,[WndProc]
    mov qword [wc.lpfnWndProc],rax
    mov dword [wc.cbClsExtra],NULL
    mov dword [wc.cbWndExtra],DLGWINDOWEXTRA
    mov rax,qword [hInstance]
    mov qword [wc.hInstance],rax
    mov qword [wc.hbrBackground],COLOR_BTNFACE+1
    mov qword [wc.lpszMenuName],NULL
    lea rax,ClassName
    mov qword [wc.lpszClassName],rax

    ; Shadow space (32 octets)
    sub rsp,32
    xor ecx,ecx
    mov edx,IDI_APPLICATION
    ; Chargement de l'icône de l'application
    call LoadIconA
    mov qword [wc.hIcon],rax
    mov qword [wc.hIconSm],rax
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Shadow space (32 octets)
    sub rsp,32
    xor ecx,ecx
    mov edx,IDC_ARROW
    ; Curseur de l'application
	call LoadCursorA
    mov qword [wc.hCursor],rax
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Shadow space (32 octets)
    sub rsp,32
    lea rcx,[wc]
    ; Inscrit une classe de fenêtre pour une utilisation ultérieure dans les appels à des fonctions de créatoin de fenêtre
	call RegisterClassExA
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Shadow space + 1 paramètre + 8 octets de padding (48 octets)
    sub rsp,32 + 8 + 8
    mov rcx,qword [hInstance]
    xor rdx,rdx
    mov edx,IDC_DIALOG
    xor r8,r8
    lea r9,WndProc
    mov rax,qword [hInstance]
    mov qword [rsp + 32],rax
	; Création de la fenêtre de dialogue
    call CreateDialogParamA
	mov [hDlg],rax
    ; Restauration des 48 octets de la pile
    add rsp,48

    ; Shadow space (32 octets)
    sub rsp,32
    mov rcx,SW_SHOWNORMAL
    mov rdx,[hDlg]
    ; Affichage la fenêtre
    call ShowWindow
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Shadow space (32 octets)
    sub rsp,32
    mov rcx,[hDlg]
    ; Mise à jour la fenêtre
    call UpdateWindow
    ; Restauration des 32 octets de la pile
    add rsp,32

.WHILE_TRUE:

    ; Shadow space (32 octets)
    sub rsp,32
    lea rcx,[msg]
    xor rdx,rdx
    xor r8,r8
    xor r9,r9
    ; Lecture du message de la fenêtre
    call GetMessageA
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Message de fin reçu ?
    cmp rax,0
    ; Oui
    je .FinWinMain

    ; Shadow space (32 octets)
    sub rsp,32
    ; mov rcx,[hDlg]
    lea rdx,[msg]
    ; Gestion des touches du clavier
    call IsDialogMessageA
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Exécution de TranslateMessage et DispatchMessageA ?
    cmp rax,0
    jne .WHILE_TRUE

    ; Shadow space (32 octets)
    sub rsp,32
    lea rcx,[msg]
    call TranslateMessage
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Shadow space (32 octets)
    sub rsp,32
    lea rcx,[msg]
    call DispatchMessageA
    ; Restauration des 32 octets de la pile
    add rsp,32
    
    jmp .WHILE_TRUE


.FinWinMain:
    ; Fin de la fonction WinMain

    ; Restauration du pointeur de la pile
    mov rsp,rbp
    pop rbp

    ; Fin de la fonction WinMain
    mov rax,[msg.wParam]
    ret

WndProc:
    ; Fonction de gestion des événements de la fenêtre

    push rbp
    mov rbp,rsp

    ; Récupération des valeurs envoyées à WndProc
    mov qword [hWnd],rcx
    mov qword [uMsg],rdx
    mov qword [wParam],r8
    mov qword [lParam],r9

    ; Fermeture de la fenêtre ?
    cmp qword [uMsg],WM_DESTROY
    ; Oui
    je .WMDESTROY

    ; Un message WM_COMMAND ?
    cmp qword [uMsg],WM_COMMAND
	jne .NO_WM_COMMAND

    ; Oui

    ; WM_COMMAND

    ; Vérification de lParam
    cmp qword [lParam],0
    je .END_WNDPROC
	
    ; Récupération de wParam pour savoir si c'est un bouton
    mov rax,qword [wParam]
    shr eax,16

    ; Un bouton a été apppuyé ?
    cmp ax,BN_CLICKED
    jne .END_WNDPROC

    mov rax,qword [wParam]
    ; Le bouton CANCEL ?
    cmp ax,IDC_BUTTONCANCEL
    jne .NO_BUTTONCANCEL

    ; Bouton CANCEL

    ; Fermeture de la boîte de dialogue (on quitte le programme)

    ; Shadow space (32 octets)
    sub rsp,32
    mov rcx,qword [hWnd]
    mov rdx,WM_CLOSE
    mov r8,NULL
    mov r9,NULL
    call SendMessageA
    ; Restauration des 32 octets de la pile
    add rsp,32

    jmp .END_WNDPROC

.NO_BUTTONCANCEL:

    cmp ax,IDC_BUTTONOK
    jne .END_WNDPROC

    ; Bouton OK

    ; Fermeture de la boîte de dialogue (on quitte le programme)

    ; Shadow space (32 octets)
    sub rsp,32
    mov rcx,qword [hWnd]
    mov rdx,WM_CLOSE
    mov r8,NULL
    mov r9,NULL
    call SendMessageA
    ; Restauration des 32 octets de la pile
    add rsp,32

    jmp .END_WNDPROC

.NO_WM_COMMAND:

    ; Gestion par défaut de la fenêtre

    ; Shadow space (32 octets)
    sub rsp,32
    mov rcx,qword [hWnd]
    mov rdx,qword [uMsg]
    mov r8,qword [wParam]
    mov r9,qword [lParam]
    ; Action par défaut
    call DefWindowProcA
    ; Restauration des 32 octets de la pile
    add rsp,32

    ; Restaure la pile
    mov rsp,rbp
    pop rbp
    
    ; Quitte la fonction
    ret

.WMDESTROY:
    ; Réception d'une commande de fermeture de la fenêtre

    ; Shadow space (32 octets)
    sub rsp,32
    xor rcx,rcx
    ; Message de fermeture au système
    call PostQuitMessage
    ; Restauration des 32 octets de la pile
    add rsp,32

.END_WNDPROC:

    ; Restaure la pile
    mov rsp,rbp
    pop rbp

    ; Quitte la fonction et retourne 0
    xor rax,rax
    ret
```

dialogoxparam.rc
``` c
#include <WINUSER.H>

#define IDC_DIALOG 200
#define IDC_GROUPBOXINFORMATION1 1001
#define IDC_STATICTEXT1 1002
#define IDC_EDIT1 1003
#define IDC_BUTTONOK 1004
#define IDC_BUTTONCANCEL 1005

IDC_DIALOG DIALOGEX 0, 0, 250, 100
STYLE DS_SETFONT | DS_MODALFRAME | DS_CENTER | WS_MINIMIZEBOX | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Window"
CLASS "ClasseDLG"
FONT 0,""
{
   CONTROL " Information ",IDC_GROUPBOXINFORMATION1,"BUTTON",BS_GROUPBOX,1,2,244,92
   CONTROL "Texte",IDC_STATICTEXT1,"STATIC",SS_LEFT | WS_VISIBLE | NOT WS_GROUP,8,22,28,10
   CONTROL "IDC_EDIT1",IDC_EDIT1,"EDIT",ES_LEFT | ES_AUTOHSCROLL | NOT WS_BORDER | WS_TABSTOP,42,23,196,8
   CONTROL "&OK",IDC_BUTTONOK,"BUTTON",BS_DEFPUSHBUTTON | WS_TABSTOP,130,78,50,11
   CONTROL "&Cancel",IDC_BUTTONCANCEL,"BUTTON",BS_PUSHBUTTON | WS_TABSTOP,187,78,50,11
}
```

# 3 - Compilation

```
nasm -f win64 dialogbox.asm
windres dialogbox.rc -O coff dialogbox.res
gcc -mwindows -nostartfiles -o dialogbox.exe dialogbox.obj dialogbox.res
```

``` powershell
d:\Prog\Assembleur\02 - Windows\03 - DialogBox>nasm -f win64 dialogbox.asm

d:\Prog\Assembleur\02 - Windows\03 - DialogBox>windres dialogbox.rc -O coff dialogbox.res

d:\Prog\Assembleur\02 - Windows\03 - DialogBox>gcc -mwindows -nostartfiles -o dialogbox.exe dialogbox.obj dialogbox.res

d:\Prog\Assembleur\02 - Windows\03 - DialogBox>dir dialogbox.*
 Le volume dans le lecteur D n’a pas de nom.
 Le numéro de série du volume est 0C0C-BE1F

 Répertoire de d:\Prog\Assembleur\02 - Windows\03 - DialogBox

04/11/2025  17:00             9 561 dialogbox.asm
04/11/2025  17:03            11 579 dialogbox.exe
04/11/2025  17:03             2 403 dialogbox.obj
04/11/2025  16:11               848 dialogbox.rc
04/11/2025  17:03               532 dialogbox.res
               5 fichier(s)           24 923 octets
               0 Rép(s)  3 052 547 092 480 octets libres

d:\Prog\Assembleur\02 - Windows\03 - DialogBox>
```

Note : le paramètre "-mwindows" permet de supprimer une fenêtre de console intempestive qui reste affichée à l'écran tant que la popup est affichée.

# 4 - Exécution

Une boîte de dialogue est affichée avec :
- Une zone d'édition
- 2 boutons qui ferment la boîte de dialogue

``` powershell
d:\Prog\Assembleur\02 - Windows\03 - DialogBox>dialogbox.exe

d:\Prog\Assembleur\02 - Windows\03 - DialogBox>
```