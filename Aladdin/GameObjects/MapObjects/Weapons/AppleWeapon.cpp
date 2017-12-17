#include "AppleWeapon.h"
#include "../../../GameComponents/Sound.h"

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
    return "Resources/MapObjects/Weapons/AppleWeapon.png";
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
		if(impactor->Id == Entity::EntityId::BossJafar)
			this->collisionWithBoss = true;
		else
		{
			Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AppleSplat.wav", "AppleSplat");
			Sound::getInstance()->play("AppleSplat", false, 1);
			this->collisionWithOroku = true;
		}
	}
	else if(impactor->Tag != Entity::EntityTypes::Aladdin && impactor->Tag != Entity::EntityTypes::DownStairsControl &&
		impactor->Tag != Entity::EntityTypes::HorizontalRope && impactor->Tag != Entity::EntityTypes::VerticalRope)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AppleSplat.wav", "AppleSplat");
		Sound::getInstance()->play("AppleSplat", false, 1);
		this->weaponCollided = true;
	}
}
