#include "FireWeapon.h"

FireWeapon::FireWeapon(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::FireWeapon;
	this->directionFireWeapon = Entity::DirectionFireWeapon::DirectionNone;
}

FireWeapon::FireWeapon()
{
	init(D3DXVECTOR3(0, 0, 0));
}

FireWeapon::~FireWeapon()
{

}

const char * FireWeapon::FileName()
{
	return "Resources/MapObjects/Weapons/FireWeapon.png";
}

int FireWeapon::TotalFrame()
{
	return 8;
}

int FireWeapon::Row()
{
	return 1;
}

int FireWeapon::Column()
{
	return 8;
}

float FireWeapon::SecondPerFrame()
{
	return 0.1f;
}

void FireWeapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
}