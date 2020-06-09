#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H
#endif

#include <Windows.h>
#include <d2d1_1.h>
#include <string>
#include <sstream>

using namespace std;
// GAME STUFF 
bool bGameRun;
const int nWidthPlayArea = 20;
const int nHeightPlayArea = 20;
int nPosX, nPosY, nFruitPosX, nFruitPosY, nScore;
// WINDOW STUFF
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}
	if (uMsg == WM_KEYDOWN) {
		wchar_t text_buffer[20] = { 0 }; //temporary buffer
		swprintf(text_buffer, _countof(text_buffer), L"\n%d <-- loool", wParam); // convert
		OutputDebugString(text_buffer); // print
		// CHANGE TITLE ACCORDING TO WHAT WAS PRESSED
		wstringstream oss;
		oss << "Did you just click: " << (char)wParam;
		SetWindowTextW(hwnd, oss.str().c_str());
		if (wParam == (int)VK_ESCAPE) {
			PostQuitMessage(0);
			return 0;
		}
		if (wParam == (int)'S') {
			OutputDebugStringA("\nKliknoles se eske"); // print
		}
	}
	DefWindowProc(hwnd, uMsg, wParam, lParam);
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"MAIN WINDOW";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	HWND windowHandle = CreateWindow(L"MAIN WINDOW", L"Testing Windows", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, nullptr, nullptr, hInstance, nullptr);
	if (!windowHandle) { int error = GetLastError(); return error; }
	ShowWindow(windowHandle, nCmdShow);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return 0;
}