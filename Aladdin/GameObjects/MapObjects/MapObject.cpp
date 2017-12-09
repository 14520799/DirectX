#include "MapObject.h"
#include "../../GameComponents/GameGlobal.h"


MapObject::MapObject()
{
    
}

MapObject::~MapObject()
{

}

bool MapObject::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

    SetPosition(position);
	SetVx(0);
	SetVy(0);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void MapObject::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

RECT MapObject::GetBound()
{
	RECT rect;

	rect.left = this->posX - this->GetWidth() / 2;
	rect.right = this->posX + this->GetWidth() / 2;
	rect.top = this->posY - this->GetHeight() / 2;
	rect.bottom = this->posY + this->GetHeight() / 2;

	return rect;
}

void MapObject::Update(float dt)
{
    mAnimation->Update(dt);
}

void MapObject::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void MapObject::Draw(D3DXVECTOR3 position, D3DXVECTOR2 transform)
{
	mAnimation->Draw(position, transform);
}

void MapObject::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(transform);
}

void MapObject::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	
}

