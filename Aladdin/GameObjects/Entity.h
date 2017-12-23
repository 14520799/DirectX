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
        None, Aladdin, Static, Ground,
		VerticalRope, VerticalRopeControl, HorizontalRope, Fire, FireControl, AppleWeapon,
		Stairs, UpStairs, UpStairsControl, CenterStairs, DownStairs, DownStairsControl, GroundControl, FallControl,
		Oroku, OrokuControl, Sword, Pot, ObjStairs, Spring, SpringAction, StarWeapon, FireWeapon, Bin, JasMine,
		Item, TranslateScene
    };

	enum EntityId
	{
		Guard, Camel, CivilianWindow, CivilianCircus, CivilianBasket, BossJafar,
		AppleItem, Ruby, Life, Heart, HeadGenie, Lamp, LampAttack,
		Revitalization_Default, Revitalization_Action, Revitalization_ActionStop,
		Feddler_Standing, Feddler_Magic, Feddler_MagicStop,
		ItemEffect_1, ItemEffect_2, StarEffect, FireEffect, OrokuEffect
	};
	
	enum EntityCurrentMoveStairs
	{
		CurrentNone, CurrentUpStairs, CurrentDownStairs, CurrentGround
	};

	enum DirectionFireWeapon
	{
		DirectionNone,
		DirectionLeft,
		DirectionRight
	};

    EntityTypes Tag; //Tag de nhan dien loai Entity

	EntityId Id; //Id de nhan dien loai oroku

	EntityCurrentMoveStairs CurrentMoveStairs; //MoveStairs luu trang thai hien tai cua player khi toi noi co nhieu cau thang len xuong

	DirectionFireWeapon directionFireWeapon;

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

	virtual void Draw(D3DXVECTOR2 transform);

    //kiem soat viec va cham
    //khi xay ra va cham voi 1 thuc the nao do thi ham nay se dc goi de xu ly
    virtual void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);

	//vi tri tam position x va y
	float posX, posY;
	//mau cua entity
	int bloodOfEntity;
	int preBloodOfEntity;
	//huong nem qua tao da duoc nem ra se khong doi huong
	bool mSettingRightItem;
	bool mSettingLeftItem;
	//huong chay toi tan cong cua oroku
	bool mSettingRightRun;
	bool mSettingLeftRun;
	//huong tan cong cua oroku
	bool mSettingRightAttack;
	bool mSettingLeftAttack;
	//xu ly cach nem tao
	bool DirectionDown;
	//xu ly di xuong cau thang
	bool collisionStairs;
	bool allowFalling;
	//khi bi trung don thi se duoc 0.5s mien sat thuong
	bool allowImunity;
	//khi player cham vao item se co hieu ung xuat hien
	bool allowItemEffect;
	//khi player giet oroku thi hieu ung no xuat hien
	bool allowOrokuEffect;
	//khi player giet boss thi hieu ung no xuat hien
	bool allowBossEffect;
	bool effectLamp; //khi cham vao cay den thi se tao ra hieu ung cho no
	bool effectSpecial; //khi an duoc nhung item nhu life hay headgenie thi se tao ra hieu ung khac binh thuong
	bool effectFire;

	bool collisionWithOroku;
	bool collisionWithBoss;
	bool collisionWithCamel;
	bool weaponCollided; //qua tao hoac kiem khi va cham xuong dat hay tuong thi se mat
	bool collisionWithPlayer;

	D3DXVECTOR3 mOriginPosition;
	D3DXVECTOR3 mRevivalPosition;
	D3DXVECTOR3 mOriginPositionItem; //vi tri cua effect khi oroku do bi giet
protected:

    //duoc goi khi set position cua Entity, dung cho ke thua
    virtual void OnSetPosition(D3DXVECTOR3 pos);

    //phan toc vx, vy
    float vx, vy;

    //size cua entity
    float width, height;
};