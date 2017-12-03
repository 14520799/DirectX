#include "AppleWeapon.h"

AppleWeapon::AppleWeapon(D3DXVECTOR3 position)
{
    init(position);
}

AppleWeapon::AppleWeapon()
{
	init(D3DXVECTOR3(0, 0, 0));
}

AppleWeapon::~AppleWeapon()
{

}

const char * AppleWeapon::FileName()
{
    return "Resources/Items/Apple/AppleWeapon.png";
}

int AppleWeapon::TotalFrame()
{
    return 1;
}

int AppleWeapon::Row()
{
    return 1;
}

int AppleWeapon::Column()
{
    return 1;
}

float AppleWeapon::SecondPerFrame()
{
    return 0.0f;
}

void AppleWeapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		this->collisionWithOroku = true;
	}
	else if(impactor->Tag != Entity::EntityTypes::Aladdin && impactor->Tag != Entity::EntityTypes::Item)
	{
		this->weaponCollided = true;
	}
}