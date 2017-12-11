#include "StarWeapon.h"

StarWeapon::StarWeapon(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::StarWeapon;
}

StarWeapon::StarWeapon()
{
	init(D3DXVECTOR3(0, 0, 0));
}

StarWeapon::~StarWeapon()
{

}

const char * StarWeapon::FileName()
{
	return "Resources/MapObjects/Weapons/StarWeapon.png";
}

int StarWeapon::TotalFrame()
{
	return 3;
}

int StarWeapon::Row()
{
	return 1;
}

int StarWeapon::Column()
{
	return 3;
}

float StarWeapon::SecondPerFrame()
{
	return 0.05f;
}

void StarWeapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
}