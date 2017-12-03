#include "PlayerState.h"
#include "Player.h"

class PlayerDeathState : public PlayerState
{
public:
	PlayerDeathState(PlayerData *playerData);
	~PlayerDeathState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	//void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
	float timeDelayHurting;

	bool allowDelayHurting; //cho phep mot khoang thoi gian danh cho animationDeath
};