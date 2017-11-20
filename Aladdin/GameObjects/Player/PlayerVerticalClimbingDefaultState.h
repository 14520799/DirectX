#include "Player.h"
#include "PlayerState.h"

class PlayerVerticalClimbingDefaultState : public PlayerState
{
public:
	PlayerVerticalClimbingDefaultState(PlayerData *playerData);
	~PlayerVerticalClimbingDefaultState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};