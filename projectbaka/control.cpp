#include "game/bakagame.h"
#include <Windows.h>
#include "core/bthread.h"
void GameControl::_set_game_state(state state) {
	this->game_state_ = state;
}

void GameControl::_game_loop() {
	
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
			this->do_begin();
			break;
		}
	case GAME_STATE_LOADING_END:
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

/**
 * \brief  GameInitThread
 * 
 */
class GameInitThread :public bThread {
private:
	GameControl *gc = nullptr;
public:
	GameInitThread(GameControl* gc);
	~GameInitThread();
	void action() override;
};

GameInitThread::GameInitThread(GameControl *gc) {
	this ->gc = gc;
	
}

GameInitThread::~GameInitThread() {
	CloseHandle(b_thread);
}

void GameInitThread::action() {
	gc->game_loading();
	delete this;
}
void GameControl::game_loading() {
	do_begin();
	this->game_state_ = GameControl::GAME_STATE_LOADING_END;
}
void GameControl::initialize() {
	this->game_state_ = GameControl::GAME_STATE_LOADING;
	do_init();
	GameInitThread *temp = new GameInitThread(this);
	temp->start();
	
}

void GameControl::wait_loading_end() {
	while (this->game_state_ == GameControl::GAME_STATE_LOADING);
	return;
}

bool GameControl::loading_end() const {
	return this->game_state_ == GAME_STATE_LOADING_END;
}
unsigned int  GameControl::get_state() {
	return this->game_state_;
}
void GameControl::do_begin() {
}

void GameControl::do_init() {
}


void GameControl::add_acion(std::string name, GameAction& game_action) {
	this->ActionSet[name] = &game_action;
}


GameControl::~GameControl() {

}

void GameControl::do_user_scene(std::string) {
}


