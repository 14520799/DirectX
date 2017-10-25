#include "Player.h"
#include "PlayerState.h"

class PlayerHorizontalClimbingThrowAppleState : public PlayerState
{
public:
	PlayerHorizontalClimbingThrowAppleState(PlayerData *playerData);
	~PlayerHorizontalClimbingThrowAppleState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};