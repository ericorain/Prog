# 1 - Description

Création d'une popup simple sous Windows en C avec GCC.

# 2 - Code

messagebox.c
``` c
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int nShowCmd)
{
  MessageBox(NULL, "Message", "Titre", MB_OK);
  return 0;
}
```

# 3 - Compilation

```
gcc -mwindows -o messagebox.exe messagebox.c
```

``` powershell
d:\data\git\programming\c\01 - Messagebox>gcc -mwindows -o messagebox.exe messagebox.c

d:\data\git\programming\c\01 - Messagebox>
d:\data\git\programming\c\01 - Messagebox>dir
 Le volume dans le lecteur D n’a pas de nom.
 Le numéro de série du volume est 0C0C-BE1F

 Répertoire de d:\data\git\programming\c\01 - Messagebox

02/11/2025  17:05    <DIR>          .
02/11/2025  17:04    <DIR>          ..
02/11/2025  17:05               183 messagebox.c
02/11/2025  17:05            55 102 messagebox.exe
               2 fichier(s)           55 285 octets
               2 Rép(s)  3 062 195 380 224 octets libres

d:\data\git\programming\c\01 - Messagebox>
```

Note : le paramètre "-mwindows" permet de supprimer une fenêtre de console intempestive qui reste affichée à l'écran tant que la popup est affichée.

# 4 - Exécution

Une popup est affichée avec un bouton "OK".

``` powershell
d:\data\git\programming\c\01 - Messagebox>messagebox.exe

d:\data\git\programming\c\01 - Messagebox>
```