#include "FeddlerMagicStop.h"

FeddlerMagicStop::FeddlerMagicStop(D3DXVECTOR3 position)
{
	init(position);
}

FeddlerMagicStop::FeddlerMagicStop()
{
	init(D3DXVECTOR3(0, 0, 0));
}

FeddlerMagicStop::~FeddlerMagicStop()
{

}

const char * FeddlerMagicStop::FileName()
{
	return "Resources/MapObjects/Items/FeddlerMagicStop.png";
}

int FeddlerMagicStop::TotalFrame()
{
	return 5;
}

int FeddlerMagicStop::Row()
{
	return 1;
}

int FeddlerMagicStop::Column()
{
	return 5;
}

float FeddlerMagicStop::SecondPerFrame()
{
	return 0.2f;
}