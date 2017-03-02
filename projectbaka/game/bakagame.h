
#include "core/bakamain.h"
#pragma once
typedef DWORD state;
//a game action! an action will be down sometimes.
class BAKADLL GameAction {
public:
	virtual ~GameAction() = default;
	virtual void do_action()=0;
};
//a game scene , not yet finished
class BAKADLL GameScene {
public:
	virtual ~GameScene() = default;
	virtual void show_scene() = 0;
};
//game control ,the basic one of the framework ,new a son-class of GameControl and rewrite its function to start the game.use do_begin() to initialize base component and use do_loading() to initialize aming object.
class BAKADLL GameControl {
private:
	std::map<std::string, GameAction*> ActionSet;
	std::map<std::string, GameScene*> SceneSet;
protected:
	BakaEnvironment *control_baka;
	state game_state_;
	const static state GAME_STATE_BEGIN = 0x01;
	const static state GAME_STATE_LOADING_END = 0x03;
	const static state GAME_STATE_LOADING = 0x02;
	const static state GAME_STATE_GAMING = 0x04;
	void _set_game_state(state state);
	void _game_loop();
	
	void _JumpToState(state state);
public:
	virtual ~GameControl();
	DWORD _set_fps(DWORD FPS);
	void add_scene(std::string ,GameScene& game_scene);
	void add_scene(std::string, GameScene* game_scene);
	void add_acion(std::string, GameAction&);
	void add_acion(std::string, GameAction*);
	void game_loading();
	void initialize();
	void wait_loading_end();
	bool loading_end() const;
	unsigned get_state();
	virtual void do_begin();
	virtual void do_init();
	virtual void do_end() { return; }
	/**
	 * \brief 
	 */
	virtual void do_gaming() { return; }
	void game_start();
	static DWORD WINAPI game_looping(void* args);
	virtual void while_loading() { return; }
	virtual void while_gaming() { return; }
	virtual void do_loading() { return; }
	virtual void do_user_scene(std::string);
	void init(BakaEnvironment *be);
};