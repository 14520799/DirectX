#include "Stairs.h"
#include "../../../GameDefines/GameDefine.h"

Stairs::Stairs(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::ObjStairs;
}

Stairs::Stairs()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Stairs::~Stairs()
{

}

const char * Stairs::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Stairs.png";
}

int Stairs::TotalFrame()
{
	return 1;
}

int Stairs::Row()
{
	return 1;
}

int Stairs::Column()
{
	return 1;
}

float Stairs::SecondPerFrame()
{
	return 0.0f;
}

void Stairs::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
}