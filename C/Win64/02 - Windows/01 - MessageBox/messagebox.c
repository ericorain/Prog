#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int nShowCmd)
{
  MessageBox(NULL, "Message", "Titre", MB_OK);
  return 0;
}