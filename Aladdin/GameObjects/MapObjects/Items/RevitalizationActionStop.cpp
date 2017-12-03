#include "RevitalizationActionStop.h"

RevitalizationActionStop::RevitalizationActionStop(D3DXVECTOR3 position)
{
	init(position);
}

RevitalizationActionStop::RevitalizationActionStop()
{
	init(D3DXVECTOR3(0, 0, 0));
}

RevitalizationActionStop::~RevitalizationActionStop()
{

}

const char * RevitalizationActionStop::FileName()
{
	return "Resources/Items/Revitalization/RevitalizationActionStop.png";
}

int RevitalizationActionStop::TotalFrame()
{
	return 1;
}

int RevitalizationActionStop::Row()
{
	return 1;
}

int RevitalizationActionStop::Column()
{
	return 1;
}

float RevitalizationActionStop::SecondPerFrame()
{
	return 0.0f;
}