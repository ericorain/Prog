#include <windows.h>

// Fonction de la fenêtre
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0L;
}

// Fonction principale
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int nShowCmd)
{

    // Variables
    HWND hWnd;
    WNDCLASS wc;
    MSG msg;

    // Définition de la classe de la fenêtre
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance; /* <Instance de l'application> */
    wc.lpfnWndProc = WndProc; /* <Adresse d'une procédure de fenêtre> */
    wc.lpszClassName = "ClasseFenetre";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    // Enregistrement de la classe de la fenêtre
    RegisterClass(&wc);

    // Création de la fenêtre
    hWnd = CreateWindow("ClasseFenetre",     /* Classe de la fenêtre */
                        "Titre",             /* Titre de la fenêtre */
                        WS_OVERLAPPEDWINDOW, /* Style de la fenêtre */
                        100,                 /* Abscisse du coin supérieur gauche */
                        100,                 /* Ordonnée du coin supérieur gauche */
                        600,                 /* Largeur de la fenêtre */
                        300,                 /* Hauteur de la fenêtre */
                        NULL,                /* Fenêtre parent */
                        NULL,                /* Menu */
                        hInstance,           /* Instance de l'application */
                        NULL);               /* Paramètres additionnels */

    // Affichage de la fenêtre
    ShowWindow(hWnd, SW_SHOW);

    // Traitement des messages de la fenêtre
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Fin du programme
    return 0;
}