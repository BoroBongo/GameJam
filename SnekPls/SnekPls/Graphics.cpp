#include "Graphics.h"



Graphics::Graphics()
{
	factory = nullptr;
	renderTarget = nullptr;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);
	if (res != S_OK) return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r,g,b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius),brush, 3.0f);

	brush->Release();
}

void Graphics::DrawRectangle(float x, float y, float r, float g, float b, float a, float width, float height)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);


	renderTarget->DrawRectangle(D2D1::RectF(x, y, x+width, y+height), brush, 3.0f);

	brush->Release();
}


void Graphics::DrawPlayground(Playground* playground, float x, float y, float width)
{
	int h = *(playground->getHeight());
	int w = *(playground->getWidth());
	vector<vector<char> > items = *(playground->getArray());

	for (int i = 0; i < h;i++) {
		for (int j = 0; j < w; j++) {
			this->DrawRectangle(x, y, 0.5, 0.5, 1, 1, width, width);
			x += width;
		}
		x -= (width * w);
		y += width;
	}

}
