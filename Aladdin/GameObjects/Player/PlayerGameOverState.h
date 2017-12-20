#include "PlayerState.h"
#include "Player.h"

class PlayerGameOverState : public PlayerState
{
public:
	PlayerGameOverState(PlayerData *playerData);
	~PlayerGameOverState();

	void Update(float dt);

	virtual PlayerState::StateName GetState();
protected:
	float timeDelay;
};