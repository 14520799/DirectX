#include "RevitalizationAction.h"

RevitalizationAction::RevitalizationAction(D3DXVECTOR3 position)
{
	init(position);
}

RevitalizationAction::RevitalizationAction()
{
	init(D3DXVECTOR3(0, 0, 0));
}

RevitalizationAction::~RevitalizationAction()
{

}

const char * RevitalizationAction::FileName()
{
	return "Resources/MapObjects/Items/RevitalizationAction.png";
}

int RevitalizationAction::TotalFrame()
{
	return 10;
}

int RevitalizationAction::Row()
{
	return 1;
}

int RevitalizationAction::Column()
{
	return 10;
}

float RevitalizationAction::SecondPerFrame()
{
	return 0.1f;
}
