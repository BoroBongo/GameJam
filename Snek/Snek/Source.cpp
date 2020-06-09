#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include <d2d1_3.h>
#include <iostream>


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
	DefWindowProc(hwnd, uMsg, wParam, lParam);
	return 0;
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"Main Window";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	HWND windowHandle = CreateWindow(L"Main Window", L"AWESOME MAN!", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, nullptr, nullptr, hInstance, nullptr);
	if (!windowHandle) return -1;

	ShowWindow(windowHandle,nCmdShow);

	return 0;
}