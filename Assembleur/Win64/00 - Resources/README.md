# Détails des programmes Windows Win64

## Appel des fonctions Windows

Plusieurs point sont à considérer avec les appels de fonctions Windows :

- Les quatre premiers arguments entiers envoyés à une fonction sont transmis dans les registres RCX, RDX, R8 et R9, dans cet ordre. Les arguments entiers supplémentaires sont transmis sur la pile. Ces registres, ainsi que RAX, R10 et R11, sont modifiés par les appels de fonction et peuvent donc être utilisés par la fonction sans qu'il soit nécessaire de les sauvegarder.

- Les valeurs de retour entières sont transmises uniquement dans le registre RAX.

- Il est nécessaire que les fonctions allouent un « espace d'ombre » (shadow space) pour les fonctions appelées, avant de les appeler. Cet espace appartient à la fonction appelée et lui permet de stocker (facultativement) les arguments transmis par les registres (par exemple, à des fins de débogage), ou toute autre valeur souhaitée. Cet espace d'ombre de 32 octets doit être alloué juste avant l'espace de pile utilisé pour les arguments non transmis par les registres (à partir du 5ème argument, le cas échéant).

- Avant un appel de fonction, un alignement de la pile sur 16 octets est requis.

- Liens :
https://www.nasm.us/docs/3.01/nasm13.html
https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170

# Syntaxe de NASM

- Lien :
https://www.nasm.us/docs.html

# Exemples en Win64 avec NASM

- Lien :
https://www.davidgrantham.com/

# Exemples de fenêtres avec NASM32
- Lien :
https://nasm32.com/samples/template/template.html

