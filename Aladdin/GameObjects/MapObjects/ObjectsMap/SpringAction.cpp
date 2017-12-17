#include "SpringAction.h"
#include "../../../GameDefines/GameDefine.h"

SpringAction::SpringAction(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::SpringAction;
}

SpringAction::SpringAction()
{
	init(D3DXVECTOR3(0, 0, 0));
}

SpringAction::~SpringAction()
{

}

const char * SpringAction::FileName()
{
	return "Resources/MapObjects/ObjectsMap/SpringAction.png";
}

int SpringAction::TotalFrame()
{
	return 3;
}

int SpringAction::Row()
{
	return 1;
}

int SpringAction::Column()
{
	return 3;
}

float SpringAction::SecondPerFrame()
{
	return 0.05f;
}