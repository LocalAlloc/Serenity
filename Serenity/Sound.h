#include <Windows.h>
#include <math.h>
#pragma comment(lib, "winmm.lib")
//extern VOID WINAPI AudioPayloadThread(VOID);
extern DWORD WINAPI AudioPayloadThread(LPVOID lpParam);
#pragma warning(disable: 4838)
#pragma warning(disable: 4293)
#pragma warning(disable: 4244)

extern HANDLE g_terminateEvent; // Declare the global event handle
extern HANDLE Voice; // Declare the thread handle