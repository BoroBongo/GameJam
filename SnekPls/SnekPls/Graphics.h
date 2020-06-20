#pragma once
#include <d2d1.h>
#include "dwrite.h"
#include "Playground.h"
#include <string>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	IDWriteFactory* writeFactory;
	IDWriteTextFormat* TextFormat;
	IDWriteTextLayout* TextLayout;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	HRESULT CreateDeviceIndependentResources();

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float x, float y, float r, float g, float b, float a, float width, float height);

	void DrawSomeText(float x, float y, float r, float g, float b, float a, const std::wstring& string1);

	void DrawPlayground(Playground* playground, float x, float y, float width, float r, float g, float b, float a);
};

