#include "AppleGod.h"

AppleGod::AppleGod(D3DXVECTOR3 position)
{
	init(position);
}

AppleGod::~AppleGod()
{

}

const char * AppleGod::FileName()
{
	return "Resources/Items/Apple/AppleGod.png";
}

int AppleGod::TotalFrame()
{
	return 9;
}

int AppleGod::Row()
{
	return 1;
}

int AppleGod::Column()
{
	return 9;
}

float AppleGod::SecondPerFrame()
{
	return 0.05f;
}