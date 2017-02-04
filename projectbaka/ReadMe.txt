========================================================================
    DYNAMIC LINK LIBRARY : projectbaka Project Overview
========================================================================
Now Render can render images.
a test demo could go look like that:

#include <bakagame.h>
#include <textureset.h>
#include <sprite.h>
#include <render_system.h>
#pragma comment(lib, "projectbaka.lib")
TextureManager *t;
BakaEnvironment *baka;
Render *render;
void LoadTexture() {
	t = baka->getTextureManagerInstance();
	t->TextureLoadBitmap(L"test.jpg", "test");
}
void RenderInit() {
	SpriteBase *sprite = new SpriteBase();
	t->AttachToSprite(sprite, "test");
	render = Render::getRender(baka, Render::STATE_FIXED);
	render->AddSprite(sprite);
}

void InitBaka() {
	baka = new BakaEnvironment(100, 100, 500, 500);
	baka->Init();
	LoadTexture();
	RenderInit();
}
int BakaMain() {
	InitBaka();
	baka->BakaStart();
}
