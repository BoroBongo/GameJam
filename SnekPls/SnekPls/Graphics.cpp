#include "Graphics.h"

typedef basic_string<wchar_t> wstring;


Graphics::Graphics()
{
	factory = nullptr;
	renderTarget = nullptr;
	writeFactory = nullptr;
	TextFormat = nullptr;
	TextLayout = nullptr;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (TextFormat) TextFormat->Release();
	if (TextLayout) TextLayout->Release();
	if (renderTarget) renderTarget->Release();
	if (writeFactory) writeFactory->Release();
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

HRESULT Graphics::CreateDeviceIndependentResources()
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	static const WCHAR msc_fontName[] = L"Comic Sans";
	static const FLOAT msc_fontSize = 12;

	if (SUCCEEDED(res))
	{

		// Create a DirectWrite factory.
		res = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(writeFactory),
			reinterpret_cast<IUnknown**>(&writeFactory)
		);
	}
	if (SUCCEEDED(res))
	{
		// Create a DirectWrite text format object.
		res = writeFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&TextFormat
		);
	}
	if (SUCCEEDED(res))
	{
		// Center the text horizontally and vertically.
		TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);


	}

	return res;
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

void Graphics::DrawSomeText(float x, float y, float r, float g, float b, float a, const std::wstring& string1)
{
	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();
	HRESULT res = CreateDeviceIndependentResources();
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	//res = writeFactory->CreateTextLayout(text.c_str(), size, TextFormat, renderTargetSize.width, renderTargetSize.height, &TextLayout);

	renderTarget->DrawTextW(string1.c_str(), string1.size(), TextFormat, D2D1::RectF(x-240.0f, y-240.0f, renderTargetSize.width, renderTargetSize.height), brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
	//renderTarget->DrawTextLayout(D2D1::Point2F((x-240.0f),(y-240.0f)),TextLayout,brush,D2D1_DRAW_TEXT_OPTIONS_NONE);
	brush->Release();
}


void Graphics::DrawPlayground(Playground* playground, float x, float y, float width, float r, float g, float b, float a, float elapsed_f)
{
	int h = *(playground->getHeight());
	int w = *(playground->getWidth());
	wstring check = L"0";
	vector<vector<wstring> >& items = *(playground->getArray());
	for (int i = 0; i < h;i++) {
		for (int j = 0; j < w; j++) {
			this->DrawRectangle(x, y, 0.5, 0.5, 1, 1, width, width);
			this->DrawSomeText((x-390.0f)+(j*width), (y-290.0f)+(i*width), r, g, b, 0.3f, items[i][j]);
			if (items[i][j]==L"X") {
				this->DrawCircle((x+12.5f), (y+12.5f), 7.0f, r, g, b, a);
			}
			if (items[i][j] == L"B") {
				this->DrawCircle((x + 12.5f), (y + 12.5f), 7.0f, b, g, g, a);
			}
			x += width;
		}
		x -= (width * w);
		y += width;
	}
}
