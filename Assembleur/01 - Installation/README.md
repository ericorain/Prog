# Introduction

MASM32 est un outil qui dispose d'un SDK bien pratique pour réaliser des programmes win32 en assembleur. Toutefois, lorsqu'il s'agit de créer un programme en assembleur win64, il ne convient plus et son successeur MASM64 SDK existe en version bêta et son téléchargement est refusé par Chrome (même en désactivant la sécurité) et Edge qui le voit tous les deux comme un virus. De plus le programme ml64.exe (l'assembleur) n'est plus mis à jour depuis 

La solution pour assembler et lier un code en assembleur 64 bits sera donc :

- Pour l'assemblage
	- nasm

- Pour le linkage
	- GCC pour le linkage

Liens :

- NASM
	- https://www.nasm.us/
- GCC
	- https://github.com/niXman/mingw-builds-binaries/releases

Autres liens :

- MASM32 SDK
	- https://masm32.com/
- MASM64 SDK
	- https://masm32.com/board/index.php?board=53.0

# Installation de NASM

## 1 - Téléchargement de NASM

Rien de plus facile : il suffit de se rendre sur le site de NASM et de récupérer l'archive "Stable".

- Exemple :
https://www.nasm.us/pub/nasm/releasebuilds/3.01/win64/nasm-3.01-win64.zip

- Lien du site :
https://www.nasm.us/

## 2 - Décompression de l'archive

Décompressez l'archive est récupérez le fichier "nasm.exe". Mettez-le dans un répertoire "nasm" (exemple "c:\nasm").

## 3 - Ajout du chemin de NASM dans le PATH

1. Appuyez sur les touches Windows+Pause puis "Paramètres avancés du système" (ou Windows+R puis vous lancez "sysdm.cpl" puis sélectionnez l"onglet "Paramètres système avancés").
2. Cliquez sur le bouton "Variables d'environnement".
3. Dans "Variables système" (en bas) recherchez la variable d'environnement "Path".
4. Rajoutez la valeur suivante :

```
c:\nasm\
```

NASM est prêt à être utilisé.

# Installation de GCC

- Instructions
https://phoenixnap.com/kb/install-gcc-windows

## 1 - Récupération du programme GCC pour Windows dans MinGW-w64

Depuis le dépôt github de MinGW-w64 se trouve ici :
https://github.com/niXman/mingw-builds-binaries/releases

Il faut récupérer l'archive ayant un nom contenant "x86_64" et "release-posix-seh-ucrt".

- Exemple :
```
x86_64-15.2.0-release-posix-seh-ucrt-rt_v13-rev0.7z
```

## 2 - Décompression de l'archive à la racine du disque dur

Il n'y a pas d'installation à réaliser, juste ouvrir l'archive avec 7zip (https://www.7-zip.org/). En ouvrant l'archive 7zip, on trouve le répertoire "mingw64" ; il suffit de copier ce dernier en le décompressant à la racine du lecteur C.

## 3 - Ajout du chemin de GCC dans le PATH

1. Appuyez sur les touches Windows+Pause puis "Paramètres avancés du système" (ou Windows+R puis vous lancez "sysdm.cpl" puis sélectionnez l"onglet "Paramètres système avancés").
2. Cliquez sur le bouton "Variables d'environnement".
3. Dans "Variables système" (en bas) recherchez la variable d'environnement "Path".
4. Rajoutez la valeur suivante :

```
c:\mingw64\bin\
```

5. Validez votre choix.

## 4 - Test de GCC

Tapez "gcc -v" dans une invite de commande. Vous devriez avoir ceci :

``` powershell
PS D:\> gcc -v
Using built-in specs.
COLLECT_GCC=c:\mingw64\bin\gcc.exe
COLLECT_LTO_WRAPPER=C:/mingw64/bin/../libexec/gcc/x86_64-w64-mingw32/15.2.0/lto-wrapper.exe
Target: x86_64-w64-mingw32
Configured with: ../../../src/gcc-15.2.0/configure --host=x86_64-w64-mingw32 --build=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --prefix=/mingw64 --with-sysroot=/c/buildroot/x86_64-1520-posix-seh-ucrt-rt_v13-rev0/mingw64 --enable-host-shared --disable-multilib --enable-languages=c,c++,fortran,lto --enable-libstdcxx-time=yes --enable-threads=posix --enable-libgomp --enable-libatomic --enable-lto --enable-graphite --enable-checking=release --enable-mingw-wildcard --enable-fully-dynamic-string --enable-version-specific-runtime-libs --enable-libstdcxx-filesystem-ts=yes --disable-libssp --disable-libstdcxx-pch --disable-libstdcxx-debug --enable-bootstrap --disable-rpath --disable-win32-registry --disable-nls --disable-werror --disable-symvers --with-gnu-as --with-gnu-ld --with-arch=nocona --with-tune=core2 --with-libiconv --with-system-zlib --with-gmp=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-mpfr=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-mpc=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-isl=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-pkgversion='x86_64-posix-seh-rev0, Built by MinGW-Builds project' --with-bugurl=https://github.com/niXman/mingw-builds LD_FOR_TARGET=/c/buildroot/x86_64-1520-posix-seh-ucrt-rt_v13-rev0/mingw64/bin/ld.exe --with-boot-ldflags='-pipe -fno-ident -L/c/buildroot/x86_64-1520-posix-seh-ucrt-rt_v13-rev0/mingw64/opt/lib -L/c/buildroot/prerequisites/x86_64-zlib-static/lib -L/c/buildroot/prerequisites/x86_64-w64-mingw32-static/lib  -Wl,--disable-dynamicbase -static-libstdc++ -static-libgcc'
Thread model: posix
Supported LTO compression algorithms: zlib
gcc version 15.2.0 (x86_64-posix-seh-rev0, Built by MinGW-Builds project)
PS D:\>
```

# Installation de windres

 windres qui sert à la génération de fichier .res depuis des fichiers .rc se trouve installé avec GCC. Donc il n'y a pas d'installation à réaliser.

# Installation de ResourceHacker

ResourceHacker est un éditeur de ressources (fichiers .rc). Le logiciel peut s'utiliser sans installation.

Le logiciel ResourceHacker permet de créer des fichiers .rc (au format texte) ainsi que des fichiers .res (compilés).

A noter que :
- Par défaut, Resourcehacker sauve un fichier .rc en UTF16
	- Il faut recopier le texte généré dans un fichier texte en ANSI pour que windres puisse créer un fichier .res

- Pour que windres lise le fichier généré, il faut rajouter au début du fichier .rc :

```
#include <WINUSER.H>
```

- Lien :
https://www.angusj.com/resourcehacker/#download