#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H
#endif

#include <Windows.h>
#include "Graphics.h"
#include "Playground.h"
#include <sstream>
#include <ctime>


using namespace std::chrono_literals;
// GAME STUFF 
bool bGameRun;
const int nWidthPlayArea = 20;
const int nHeightPlayArea = 20;
int nPosX, nPosY, nFruitPosX, nFruitPosY, nScore;
// WINDOW STUFF
Graphics* graphics;
Playground* playground;
int nMousePos[] = { 100,100 };
float rgba[] = { 0.5, 0.5, 1,1 };
wstringstream oss;
wstring mouseClicked = L"";
string keyClicked = "";
char pressedKey;
char check = 'X';

void resetstring() {
	wstringstream ossc;
	oss.swap(ossc);
}

enum class bMouseClicked
{
	CLICKED,
	NOT_CLICKED
}; 

Playground::Moving movedir;

bMouseClicked mouseBool = bMouseClicked::NOT_CLICKED;
bMouseClicked keyBool = bMouseClicked::NOT_CLICKED;

void print(HWND hwnd) {
	resetstring();
	switch (mouseBool) {
	case bMouseClicked::CLICKED: {
			mouseClicked = L" CLICKED ";
			break;
		}
		
		case bMouseClicked::NOT_CLICKED: {
			mouseClicked = L" NOT CLICKED";
			break;
		}
	}

	switch (keyBool) {
	case bMouseClicked::CLICKED: {
		keyClicked = " CLICKED ";
		keyClicked.append(&pressedKey);
		
		break;
	}

	case bMouseClicked::NOT_CLICKED: {
		keyClicked = " ";
		break;
	}
	}

	string s = keyClicked;
	wstring wst(s.begin(),s.end());

	oss << nMousePos[0] << "  " << nMousePos[1] << " | " << mouseClicked << " | " << wst;

	SetWindowTextW(hwnd, oss.str().c_str());
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
	//case WM_PAINT: {
	//	graphics->BeginDraw();
	//	graphics->ClearScreen(0.53, 0.29, 0.62);
	//	graphics->DrawCircle(nMousePos[0],nMousePos[1],60,rgba[0],rgba[1],rgba[2],rgba[3]);
	//	graphics->EndDraw();
	//	break;
	//}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
		break;
	}
	case WM_MOUSEMOVE: {
			nMousePos[0] = (int)(short)LOWORD(lParam);
			nMousePos[1] = (int)(short)HIWORD(lParam);
		break;
	}
	case WM_LBUTTONDOWN:{
	//	oss << " " << " CLICKED ";
		mouseBool = bMouseClicked::CLICKED;
		rgba[0] = 1;
		rgba[1] = 0.56;
		rgba[2] = 0.62;
		rgba[3] = 1;
		break;
	}
	case WM_LBUTTONUP: {
	//	oss << " " << " UP ";
		mouseBool = bMouseClicked::NOT_CLICKED;
		rgba[0] = 0.5;
		rgba[1] = 0.5;
		rgba[2] = 1;
		rgba[3] = 1;
			
		break;
	}
	case WM_KEYDOWN: {
		keyBool = bMouseClicked::CLICKED;
		wchar_t text_buffer[20] = { 0 }; //temporary buffer
		swprintf(text_buffer, _countof(text_buffer), L"\n%d <-- loool", wParam); // convert
		OutputDebugString(text_buffer); // print
		// CHANGE TITLE ACCORDING TO WHAT WAS PRESSED
	pressedKey = (char)wParam;
		
	switch (wParam) {
	case VK_ESCAPE: {
		PostQuitMessage(0);
		return 0;
		break;
	}
	case VK_RIGHT: {
		
		movedir = Playground::Moving::RIGHT;
		break;
	}
	case VK_LEFT: {
		
		movedir = Playground::Moving::LEFT;
		break;
	}
	case VK_UP: {
		
		movedir = Playground::Moving::UP;
		break;
	}
	case VK_DOWN: {
		
		movedir = Playground::Moving::DOWN;
		break;
	}
	}
	break;
	}
	case WM_KEYUP: {
		keyBool = bMouseClicked::NOT_CLICKED;
		break;
	}
	default: DefWindowProc(hwnd, uMsg, wParam, lParam);
}
}

void InputCheck() {
	switch (movedir) {
	case Playground::Moving::UP: {
		playground->ClickUp();
		break;
	}
	case Playground::Moving::DOWN: {
		playground->ClickDown();
		break;
	}
	case Playground::Moving::LEFT: {
		playground->ClickLeft();
		break;
	}
	case Playground::Moving::RIGHT: {
		playground->ClickRight();
		break;
	}
	}

}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"MAIN WINDOW";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	RECT rect = {0,0,800,600};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindow(L"MAIN WINDOW", L"Testing Windows", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

	if (!windowHandle) { int error = GetLastError(); return error; }
	graphics = new Graphics();
	playground = new Playground(20,20);

	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}
	ShowWindow(windowHandle, nCmdShow);

	MSG message;
	message.message = WM_NULL;
	bool up = false;
	time_t start, end;
	std::chrono::steady_clock::time_point start1;
	start1 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point teraz;
	float elapsed_f = 0;
	while (message.message != WM_QUIT) {
		if (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE)) {
			//anslateMessage(&message);
			//If there is a message, dipsatch to window proc
			DispatchMessage(&message);
			print(windowHandle);
		}
		else{
			// UPDATE!
			//RENDER
			graphics->BeginDraw();
			graphics->ClearScreen(0.53, 0.29, 0.62);
	//		graphics->DrawCircle(375.0f, 375.0f, 50.0f, rgba[0], rgba[1], rgba[2], rgba[3]);
			graphics->DrawPlayground(playground,150.0f,50.0f, 25.0f, rgba[0], rgba[2], rgba[1], rgba[3], elapsed_f);
		//	graphics->DrawSomeText(0, 0, rgba[0], rgba[2], rgba[1], rgba[3], (const wchar_t*)&check);
			//graphics->DrawSomeText((-480), (-480), 0.5, 1, 0.5, 1, L"2");
			teraz = std::chrono::steady_clock::now();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(teraz - start1);
			auto ms = milliseconds.count();
			if (milliseconds > std::chrono::milliseconds(100))
			{
				playground->move(elapsed_f);
				InputCheck();
				start1 = teraz;
			}

			graphics->EndDraw();

			print(windowHandle);
		}
	}
	return message.wParam;
	return 0;
}