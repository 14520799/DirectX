#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <map>

class Entity
{

public:

    Entity();

    enum SideCollisions
    {
        Left, //0
        Right, //1
        Top, //2
        Bottom, //3
        TopLeft, //4
        TopRight, //5
        BottomLeft, //6
        BottomRight, //7
        NotKnow
    };

    struct CollisionReturn
    {
        bool IsCollided;
        RECT RegionCollision;
    };

    enum EntityTypes
    {
        None, Aladdin, VerticalRope, HorizontalRope, Fire, Apple, Static, Guard,
    };

	enum EntityId
	{
		ThinGuard_1, ThinGuard_2, ThinGuard_3,
		FatGuard_1, FatGuard_2, FatGuard_3,
		StrongGuard_1, StrongGuard_2, StrongGuard_3
	};

    EntityTypes Tag; //Tag de nhan dien loai Entity

	EntityId Id; //Id de nhan dien Entity

    virtual RECT GetBound();

    virtual void SetPosition(float x, float y);

    virtual void SetPosition(D3DXVECTOR2 pos);

    virtual void SetPosition(D3DXVECTOR3 pos);

    virtual void AddPosition(D3DXVECTOR3 pos);

    virtual void AddPosition(D3DXVECTOR2 pos);

    virtual void AddPosition(float x, float y);

    virtual void SetWidth(int width);

    virtual int GetWidth();

    virtual void SetHeight(int height);

    virtual int GetHeight();

    virtual float GetVx();

    virtual void SetVx(float vx);

    virtual void AddVx(float vx);

    virtual float GetVy();

    virtual void SetVy(float vy);

    virtual void AddVy(float vy);

    virtual D3DXVECTOR3 GetPosition();

    virtual void Update(float dt);

    //kiem soat viec va cham
    //khi xay ra va cham voi 1 thuc the nao do thi ham nay se dc goi de xu ly
    virtual void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);

	//vi tri tam position x va y
	float posX, posY;
	//huong nem qua tao da duoc nem ra se khong doi huong
	bool mSettedRightReserve;
	bool mSettedLeftReserve;
	//huong chay toi tan cong cua oroku
	bool mSettedRightRunning;
	bool mSettedLeftRunning;
	//huong tan cong cua oroku
	bool mSettedRightAttack;
	bool mSettedLeftAttack;
protected:

    //duoc goi khi set position cua Entity, dung cho ke thua
    virtual void OnSetPosition(D3DXVECTOR3 pos);

    //phan toc vx, vy
    float vx, vy;

    //size cua entity
    float width, height;
};