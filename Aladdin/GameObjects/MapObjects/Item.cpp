#include "Item.h"
#include "Apple.h"
#include "../../GameComponents/GameGlobal.h"


Item::Item()
{
    
}

Item::~Item()
{

}

bool Item::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

    SetPosition(position);
	SetVx(0);
	SetVy(0);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void Item::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

void Item::Update(float dt)
{
    mAnimation->Update(dt);
}

void Item::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Item::Draw(D3DXVECTOR3 position, D3DXVECTOR2 transform)
{
	mAnimation->Draw(position, transform);
}

void Item::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(transform);
}

void Item::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)

{
	
}

