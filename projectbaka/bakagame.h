
#include "bakamain.h"
#pragma once
typedef DWORD state;
class BAKADLL GameControl {
protected:
	BakaEnvironment *__ControlBaka;
	state gameState;
	DWORD FPS;
	const static state GAME_STATE_BEGIN = 0x000023333;
	const static state GAME_STATE_END = 0x0000BABA;
	const static state GAME_STATE_LOADING = 0x0000CCCCC;
	const static state GAME_STATE_GAMING = 0x000066666;
	void _SetGameState(state state);
	void _GameLoop();
	DWORD _GetFrameRefreshingFrequency() {
		return FPS;
	}
	DWORD _SetFrameRefreshingFrequency(DWORD FPS);
	void _JumpToState(state state);
public:
	virtual void DoBegin();
	virtual void DoEnd() { return; }
	virtual void DoGaming() { return; }
	virtual void WhileLoading() { return; }
	virtual void WhileGaming() { return; }
	virtual void DoLoading() { return; }
	void Init(BakaEnvironment *be);
};