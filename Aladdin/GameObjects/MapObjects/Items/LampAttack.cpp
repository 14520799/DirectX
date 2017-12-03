#include "LampAttack.h"

LampAttack::LampAttack(D3DXVECTOR3 position)
{
	init(position);
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
	return "Resources/Items/Lamp/LampAttack.png";
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
	return 0.02f;
}

void LampAttack::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		this->collisionWithOroku = true;
	}
}