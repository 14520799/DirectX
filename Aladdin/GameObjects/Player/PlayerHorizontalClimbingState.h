#include "Player.h"
#include "PlayerState.h"

class PlayerHorizontalClimbingState : public PlayerState
{
public:
	PlayerHorizontalClimbingState(PlayerData *playerData);
	~PlayerHorizontalClimbingState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};