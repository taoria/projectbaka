#pragma once
#include<map>
#include<vector>
#include"sprite.h"
class RenderGroup :public std::map<int, std::vector<SpriteBase*>> {
	private:
		int id;
	public:
	void AddSprite(int level,SpriteBase* spriteBase) {(*this)[level].push_back(spriteBase);}
	void AddSprite(SpriteBase* spriteBase) {this->AddSprite(0, spriteBase);}

};
class Render {
private :
	BakaEnvironment *be;
	RenderGroup renderGroup;
	Render(BakaEnvironment *be);
public:
	static Render* getRender(BakaEnvironment *be);
	void RenderThis();
};