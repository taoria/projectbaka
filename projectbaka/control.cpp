#include "bakagame.h"
#include <Windows.h>

void GameControl::_SetGameState(state state){
	this->gameState = state;
}
void GameControl::_GameLoop()
{
	while (this->gameState != GameControl::GAME_STATE_END) {
		switch (gameState)
		{
		case GameControl::GAME_STATE_LOADING: {
			this->WhileLoading();
			break;
		}
		case GameControl::GAME_STATE_GAMING: {
			this->WhileGaming();
			break;
		}
	
		default:
			break;
		}
		Sleep(1000/FPS);
	}

}
DWORD GameControl::_SetFrameRefreshingFrequency(DWORD FPS)
{
	this->FPS = FPS;
	return 0;
}

void GameControl::_JumpToState(state state){
	switch (state)
	{
	case GAME_STATE_BEGIN: {
		this->DoBegin();
		break;
	}
	case GAME_STATE_END: {
		this->DoEnd();
		break;
	}
	case GAME_STATE_GAMING: {
		this->DoGaming();
		break;
	}
	case GAME_STATE_LOADING: {
		this->DoLoading();
		break;
	}
	default:
		break;
	}
}

void GameControl::DoBegin()
{
	DebugBox("23333");
}

void GameControl::Init(BakaEnvironment *bakaEn) {
	this->__ControlBaka = bakaEn;
	bakaEn->SetGameController(this);
}