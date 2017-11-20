#include "Player.h"
#include "PlayerState.h"

class PlayerVerticalClimbingState : public PlayerState
{
public:
	PlayerVerticalClimbingState(PlayerData *playerData);
	~PlayerVerticalClimbingState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
protected:
};