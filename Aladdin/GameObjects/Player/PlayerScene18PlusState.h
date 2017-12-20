#include "PlayerState.h"
#include "Player.h"

class PlayerScene18PlusState : public PlayerState
{
public:
	PlayerScene18PlusState(PlayerData *playerData);
	~PlayerScene18PlusState();

	void Update(float dt);

	virtual PlayerState::StateName GetState();
protected:
	float timeDelay;
};