#pragma once
#include <d2d1.h>
#include "Playground.h"

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float x, float y, float r, float g, float b, float a, float width, float height);

	void DrawPlayground(Playground* playground, float x, float y, float width);
};

