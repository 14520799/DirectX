#include "Player.h"
#include "PlayerState.h"

class PlayerHorizontalClimbingDefaultState : public PlayerState
{
public:
	PlayerHorizontalClimbingDefaultState(PlayerData *playerData);
	~PlayerHorizontalClimbingDefaultState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};