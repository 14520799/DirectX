#include "Text.h"

Text::Text()
{
}

Text::Text(std::wstring Str, int Width, int Height, bool IsItalic, D3DCOLOR Color)
{
	spriteHandler = GameGlobal::GetCurrentSpriteHandler();
	string = Str;
	width = Width;
	height = Height;
	isItalic = IsItalic;
	color = Color;
	font = NULL;
	D3DXCreateFont(
		GameGlobal::GetCurrentDevice(),
		0,
		0,
		FW_NORMAL,
		1, 
		isItalic,
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		ANTIALIASED_QUALITY, 
		FF_DONTCARE, 
		L"Arial",    
		&font);
}

Text::~Text()
{
	/*if (font) 
	{
		font->Release();
		font = NULL;
	}*/
}

void Text::Draw(D3DXVECTOR3 position)
{
	RECT rect;
	rect.left = position.x - width / 2.0f;
	rect.top = position.y - height / 2.0f;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	font->DrawTextW(NULL, string.c_str(), -1, &rect, DT_LEFT, color);
}

std::wstring Text::GetString()
{
	return string;
}

void Text::SetString(std::wstring value)
{
	string = value;
}

void Text::SetString(int value)
{
	string = std::to_wstring(value);
}
