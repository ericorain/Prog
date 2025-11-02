# 1 - Description

Affiche un texte sous PowerShell en C avec GCC.

# 2 - Code

affiche_texte.c
```c
#include <stdio.h>

int main() {
    printf("Bonjour");
    return 0;
}
```

# 3 - Compilation

```
gcc -o affiche_texte.exe affiche_texte.c
```

``` powershell
d:\data\git\programming\c\01 - Afficher un texte>gcc -o affiche_texte.exe affiche_texte.c

d:\data\git\programming\c\01 - Afficher un texte>
```

# 4 - Exécution

Affiche un texte.

``` powershell
d:\data\git\programming\c\01 - Afficher un texte>affiche_texte.exe
Bonjour
d:\data\git\programming\c\01 - Afficher un texte>
```