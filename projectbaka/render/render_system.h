#pragma once
#include<map>
#include <vector>
#include"sprite.h"
class RenderGroup :public std::map<int, std::vector<SpriteBase*>> {
	private:
		int id;
	public:
	void AddSprite(int level,SpriteBase* spriteBase) {(*this)[level].push_back(spriteBase);}
	void AddSprite(SpriteBase* spriteBase) {this->AddSprite(0, spriteBase);}

};
class BAKADLL Render {
protected :
	BakaEnvironment *be;
	RenderGroup renderGroup;
	Render(BakaEnvironment *be);
	int state;
public:
	static Render* getRender(BakaEnvironment *be,int state);
	static const int STATE_FIXED=0x233;
	static const int STATE_ACTIVE=0x2333;
	virtual void RenderThis();
	void AddSprite(int level, SpriteBase* spriteBase) { (renderGroup)[level].push_back(spriteBase); }
	void AddSprite(SpriteBase* spriteBase) { this->AddSprite(0, spriteBase); }
};
class BAKADLL SpriteRender :public Render {
public:
	SpriteRender(BakaEnvironment *be) :Render(be) {
		state = STATE_ACTIVE;
	
	}
	void RenderThis();

};
class BAKADLL FixedRender :public Render {
public:
	FixedRender(BakaEnvironment *be) :Render(be) {
		state = STATE_FIXED;
	}
	void RenderThis();

};