#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"

class MapObject : public Entity
{
public:
    ~MapObject();

	enum WeaponMode {
		Nomal, Fantastic 
	};

	WeaponMode Mode;

    void Update(float dt);
    
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
    
	void Draw(D3DXVECTOR3 position, D3DXVECTOR2 transform);

	void Draw(D3DXVECTOR2 transform);

	void OnSetPosition(D3DXVECTOR3 poks);

	virtual RECT GetBound();
	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	float timeDelayWeaponEffect;
	float timeDelayItemEffect;

	bool currentReverse;

	D3DXVECTOR3 originPos;
protected:
	MapObject();

    bool init(D3DXVECTOR3 position);

    virtual const char* FileName() = 0; // bat buoc phai override ham nay
    virtual int TotalFrame() = 0; //so frame cua animation
    virtual int Row() = 0; // so row cua resource hinh anh animation
    virtual int Column() = 0; // so cot cua resource hinh anh animation
    virtual float SecondPerFrame() = 0; //so giay de chuyen frame cua animation

	Animation *mAnimation;
};
