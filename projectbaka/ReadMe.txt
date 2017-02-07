========================================================================
    DYNAMIC LINK LIBRARY : projectbaka Project Overview
========================================================================
Now Render can render sprites.
a test demo could go look like that:

#include <game\bakagame.h>
#include <render\textureset.h>
#include <render\sprite.h>
#include <render\render_system.h>
#pragma comment(lib, "projectbaka.lib")
TextureManager *t;
BakaEnvironment *baka;
Render *render;
SpriteBase *sprite = new SpriteBase(0,0,233,233);
void LoadTexture() {
	t = baka->getTextureManagerInstance();
	t->TextureLoadBitmap(L"test.jpg", "test");
	t->TextureLoadBitmap(L"huaji.jpg", "»¬»ü");
}
void RenderInit() {
	t->AttachToSprite(sprite, "»¬»ü");
	render = Render::getRender(baka, Render::STATE_FIXED);
	render->AddSprite(sprite);
}
void InitBaka() {
	baka = new BakaEnvironment(100, 100, 500, 500);
	baka->Init();
	LoadTexture();
	RenderInit();
}
class NewGameControl :public GameControl {
private:
	int count;
public:
	 void DoBegin() {
		sprite->realX = 233;
		sprite->realY = 233;
		sprite->Rotation(177.0f);
	}
};
int BakaMain() {
	InitBaka();
	NewGameControl *newGameControl = new NewGameControl();
	newGameControl->Init(baka);
	baka->BakaStart();
}

