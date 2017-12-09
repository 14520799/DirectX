#include "FeddlerMagic.h"

FeddlerMagic::FeddlerMagic(D3DXVECTOR3 position)
{
	init(position);
}

FeddlerMagic::FeddlerMagic()
{
	init(D3DXVECTOR3(0, 0, 0));
}

FeddlerMagic::~FeddlerMagic()
{

}

const char * FeddlerMagic::FileName()
{
	return "Resources/MapObjects/Items/FeddlerMagic.png";
}

int FeddlerMagic::TotalFrame()
{
	return 14;
}

int FeddlerMagic::Row()
{
	return 2;
}

int FeddlerMagic::Column()
{
	return 7;
}

float FeddlerMagic::SecondPerFrame()
{
	return 0.07f;
}
