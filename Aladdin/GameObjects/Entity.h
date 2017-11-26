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
	//dung them CenterStairs de xu ly xoa cau thang luc ban dau
    enum EntityTypes
    {
        None, Aladdin, Static,
		VerticalRope, HorizontalRope, Fire, AppleItem, AppleWeapon,
		Stairs, UpStairs, UpStairsControl, CenterStairs, DownStairs, DownStairsControl, GroundControl, FallControl,
		Guard, Sword
    };
	
	enum EntityCurrentMoveStairs
	{
		CurrentNone, CurrentUpStairs, CurrentDownStairs, CurrentGround
	};

    EntityTypes Tag; //Tag de nhan dien loai Entity

	EntityCurrentMoveStairs CurrentMoveStairs; //MoveStairs luu trang thai hien tai cua player khi toi noi co nhieu cau thang len xuong

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
	//mau cua entity
	float bloodOfEntity;
	//huong nem qua tao da duoc nem ra se khong doi huong
	bool mSettingRightItem;
	bool mSettingLeftItem;
	//huong chay toi tan cong cua oroku
	bool mSettingRightRun;
	bool mSettingLeftRun;
	//huong tan cong cua oroku
	bool mSettingRightAttack;
	bool mSettingLeftAttack;
	//xu ly di xuong cau thang
	bool collisionStairs;
	bool allowFalling;

	bool collisionWithOroku;
	bool weaponCollided; //qua tao hoac kiem khi va cham xuong dat hay tuong thi se mat
	bool collisionWithPlayer;
protected:

    //duoc goi khi set position cua Entity, dung cho ke thua
    virtual void OnSetPosition(D3DXVECTOR3 pos);

    //phan toc vx, vy
    float vx, vy;

    //size cua entity
    float width, height;
};