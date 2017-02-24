#include "game/bakagame.h"
#include <Windows.h>

void GameControl::_set_game_state(state state) {
	this->game_state_ = state;
}

void GameControl::_game_loop() {
	while (this->game_state_ != GameControl::GAME_STATE_END) {
		switch (game_state_) {
		case GameControl::GAME_STATE_LOADING:
			{
				this->while_loading();
				break;
			}
		case GameControl::GAME_STATE_GAMING:
			{
				this->while_gaming();
				break;
			}
		
		default:
			break;
		}
//		Sleep(1000/this->control_baka->get_fixed_frames());
	}
}

DWORD GameControl::_set_fps(DWORD FPS) {
	this->control_baka->set_fps(FPS);
	return FPS;
}

/**
 * \brief 
 * \param FPS 
 * \return DWORD
 */
void GameControl::_JumpToState(state state) {
	switch (state) {
	case GAME_STATE_BEGIN:
		{
			this->_do_begin();
			break;
		}
	case GAME_STATE_END:
		{
			this->do_end();
			break;
		}
	case GAME_STATE_GAMING:
		{
			this->do_gaming();
			break;
		}
	case GAME_STATE_LOADING:
		{
			this->do_loading();
			break;
		}
	default:
		break;
	}
}

void GameControl::add_scene(std::string name, GameScene& game_scene) {
	this->SceneSet[name] = &game_scene;
}

void GameControl::add_scene(std::string name, GameScene* game_scene) {
	this->SceneSet[name] = game_scene;
}

void GameControl::add_acion(std::string name, GameAction* game_action) {
	this->ActionSet[name] = game_action;
}

void GameControl::game_loading() {
	do_init();
	do_begin();
}
void GameControl::do_begin() {
}

void GameControl::do_init() {
}


void GameControl::add_acion(std::string name, GameAction& game_action) {
	this->ActionSet[name] = &game_action;
}

void GameControl::_do_begin() {
	DebugBox("23333");
}

GameControl::~GameControl() {

}

void GameControl::do_user_scene(std::string) {
}


