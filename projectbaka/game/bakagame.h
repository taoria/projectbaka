
#include "core/bakamain.h"
#pragma once
typedef DWORD state;
class BAKADLL GameAction {
public:
	virtual ~GameAction() = default;
	virtual void do_action()=0;
};
class BAKADLL GameScene {
public:
	virtual ~GameScene() = default;
	virtual void show_scene() = 0;
};
class BAKADLL GameControl {
private:
	std::map<std::string, GameAction*> ActionSet;
	std::map<std::string, GameScene*> SceneSet;
protected:
	BakaEnvironment *control_baka;
	state game_state_;
	const static state GAME_STATE_BEGIN = 0x000023333;
	const static state GAME_STATE_END = 0x0000BABA;
	const static state GAME_STATE_LOADING = 0x0000CCCCC;
	const static state GAME_STATE_GAMING = 0x000066666;
	void _set_game_state(state state);
	void _game_loop();
	
	void _JumpToState(state state);
	void _do_begin();
public:
	virtual ~GameControl();
	DWORD _set_fps(DWORD FPS);
	void add_scene(std::string ,GameScene& game_scene);
	void add_scene(std::string, GameScene* game_scene);
	void add_acion(std::string, GameAction&);
	void add_acion(std::string, GameAction*);
	virtual void do_begin();
	virtual void do_end() { return; }
	virtual void do_gaming() { return; }
	void game_start();
	static DWORD WINAPI game_looping(void* args);
	virtual void while_loading() { return; }
	virtual void while_gaming() { return; }
	virtual void do_loading() { return; }
	virtual void do_user_scene(std::string);
	void init(BakaEnvironment *be);
};