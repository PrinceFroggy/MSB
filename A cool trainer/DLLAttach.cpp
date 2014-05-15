#include <windows.h>

extern void Main();

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved)
{
	if(fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Main, NULL, 0, NULL);
	}
	return TRUE;
}