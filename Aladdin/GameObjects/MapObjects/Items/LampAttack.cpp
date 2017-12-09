#include "LampAttack.h"

LampAttack::LampAttack(D3DXVECTOR3 position)
{
	init(position);
	this->Id = Entity::EntityId::LampAttack;
}

LampAttack::LampAttack()
{
	init(D3DXVECTOR3(0, 0, 0));
}

LampAttack::~LampAttack()
{

}

const char * LampAttack::FileName()
{
	return "Resources/MapObjects/Items/LampAttack.png";
}

int LampAttack::TotalFrame()
{
	return 9;
}

int LampAttack::Row()
{
	return 1;
}

int LampAttack::Column()
{
	return 9;
}

float LampAttack::SecondPerFrame()
{
	return 0.1f;
}

void LampAttack::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		this->collisionWithOroku = true;
	}
}