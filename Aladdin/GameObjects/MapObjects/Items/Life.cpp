#include "Life.h"

Life::Life(D3DXVECTOR3 position)
{
	init(position);
}

Life::~Life()
{

}

const char * Life::FileName()
{
	return "Resources/Items/Life.png";
}

int Life::TotalFrame()
{
	return 10;
}

int Life::Row()
{
	return 1;
}

int Life::Column()
{
	return 10;
}

float Life::SecondPerFrame()
{
	return 0.05f;
}