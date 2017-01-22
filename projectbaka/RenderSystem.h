#pragma once
#include<map>
#include<vector>
#include"SpriteSystem.h"
class RenderGroup :public std::map<int, std::vector<SpriteBase*>> {
	private:
		int id;
	public:
	void AddSprite(int level,SpriteBase* spriteBase) {
		(*this)[level].push_back(spriteBase);
	}
	void AddSprite(SpriteBase* spriteBase) {
		this->AddSprite(0, spriteBase);
	}
};
class Render {
public:
	RenderGroup renderGroup;
	void RenderThis();
};