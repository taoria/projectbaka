#pragma once
#include<map>
#include <vector>
#include"sprite.h"
//render group to render object by a distinguished level
class BAKADLL render_group :public std::map<int, std::vector<SpriteBase*>> , ObjectBase{
	private:
		int id;
	public:
	virtual ~render_group();
	void add_sprite(int level,SpriteBase* spriteBase) {(*this)[level].push_back(spriteBase);}
	void add_sprite(SpriteBase* spriteBase) {this->add_sprite(0, spriteBase);}

};
//renders render Sprite
class BAKADLL Render :public ObjectBase {
protected :
	BakaEnvironment *be;
	render_group renderGroup;
	explicit Render(BakaEnvironment *be);
	int state;
public:
	static Render* get_render(BakaEnvironment *be,int state);
	static const int STATE_FIXED=0x233;
	static const int STATE_ACTIVE=0x2333;
	virtual void render_this();
	void add_sprite(int level, SpriteBase* spriteBase) { (renderGroup)[level].push_back(spriteBase); }
	void add_sprite(SpriteBase* spriteBase) { this->add_sprite(0, spriteBase); }
};
//SpriteRenders render active sprite
class BAKADLL SpriteRender :public Render {
public:
	explicit SpriteRender(BakaEnvironment *be) :Render(be) {
		state = STATE_ACTIVE;
	
	}
	void render_this();

};
//Fixed Renders render fixed sprite
class BAKADLL FixedRender :public Render {
public:
	explicit FixedRender(BakaEnvironment *be) :Render(be) {
		state = STATE_FIXED;
	}
	void render_this();

};