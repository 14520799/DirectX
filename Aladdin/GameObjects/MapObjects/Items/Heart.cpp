#include "Heart.h"

Heart::Heart(D3DXVECTOR3 position)
{
	init(position);
}

Heart::~Heart()
{

}

const char * Heart::FileName()
{
	return "Resources/Items/Heart.png";
}

int Heart::TotalFrame()
{
	return 8;
}

int Heart::Row()
{
	return 1;
}

int Heart::Column()
{
	return 8;
}

float Heart::SecondPerFrame()
{
	return 0.05f;
}