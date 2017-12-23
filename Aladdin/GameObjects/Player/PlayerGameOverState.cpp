#include "PlayerGameOverState.h"
#include "PlayerRevivalState.h"
#include "../../GameControllers/SceneManager.h"
#include "../../Scenes/GameOverScene.h"

PlayerGameOverState::PlayerGameOverState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	timeDelay = 0;
}


PlayerGameOverState::~PlayerGameOverState()
{
}

void PlayerGameOverState::Update(float dt)
{
	timeDelay += dt;
	if (timeDelay > 2.5f)
	{
		Sound::getInstance()->stop("Scene1");
		Sound::getInstance()->stop("SceneFinal");
		SceneManager::GetInstance()->ReplaceScene(new GameOverScene());
	}
}

PlayerState::StateName PlayerGameOverState::GetState()
{
	return PlayerState::GameOver;
}