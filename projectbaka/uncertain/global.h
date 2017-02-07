#include "bakamain.h"
#include "sprite.h"
class Global :public WorldPart{
public:
	SpriteBase *RenderSprite[8192];
	//bool AddStaticSprite(SpriteBase *b, int x, int y);
	Global() :WorldPart(){
	}
};
class BackGround :public SpriteBase{public:


	int color=0;
	BackGround(int b) :SpriteBase(){
		color = b;
	}
	int GetColor(){
		return color;
	}

};
