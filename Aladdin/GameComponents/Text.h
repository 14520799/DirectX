#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <string>
#include "GameGlobal.h"

class Text
{
private:
	LPD3DXSPRITE spriteHandler; //SpriteHandler ho tro ve hinh

	std::wstring message;
	int width, height;
	int size;
	bool isItalic;
	D3DCOLOR color;

	LPD3DXFONT font;
public:
	Text();
	Text(std::wstring Message, int Size, int Width, int Height, bool IsItalic, D3DCOLOR Color);
	~Text();

	void Draw(D3DXVECTOR3 position);

	std::wstring GetString();
	void SetString(std::wstring value);
	void SetString(int value);
};

