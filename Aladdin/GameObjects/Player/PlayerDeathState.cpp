#include "PlayerDeathState.h"
#include "PlayerRunningState.h"

PlayerDeathState::PlayerDeathState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	this->mPlayerData->player->allowDeath = false;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	allowDelayDeath = true; //dang trong khoang thoi gian thuc hien animationDeath
	timeDelayDeath = 0;
}


PlayerDeathState::~PlayerDeathState()
{
}

void PlayerDeathState::Update(float dt)
{
	if (allowDelayDeath)
	{
		timeDelayDeath += dt;

		if (timeDelayDeath > 0.5f)
		{
			allowDelayDeath = false;
			timeDelayDeath = 0;
		}
	}
}

void PlayerDeathState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
		//cho phep thuc hien animation khac khi animationDeath thuc hien xong
		if (!allowDelayDeath)
		{
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			return;
		}
    }
}

PlayerState::StateName PlayerDeathState::GetState()
{
    return PlayerState::Death;
}