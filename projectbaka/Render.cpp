#include"core\stdafx.h"
#include "core\bakamain.h"
#include "uncertain\global.h"
#include "render\sprite.h"
#include "render\render_system.h"
void DebugInt(int x){
	char f[10];
	sprintf_s(f, "%d", x);
}

WorldPart::WorldPart()
{
	//Debug("test", "test");
	SIZE = -1;
}
WorldPart::~WorldPart()
{
	//Debug("test", "test");
	SIZE = -1;
}
bool BAKADLL abc = true;
bool BakaEnvironment::Render()
{
	//if (thisBack->GetColor() == 0){
	//	RenderSpriteGlobal(thisBack, 0,0);
	//}
	//for (int i = 0; i <= thisWorld->SIZE; i++){ 
	//	RenderSprite(thisCam, thisWorld->RenderList[i]);
	//}
	//SpriteBase *s;
	//for (int i = 0; i <= thisGlobal->SIZE; i++){
	//	s = thisGlobal->RenderList[i];
	//	RenderSpriteGlobal(s,s->realY, s->realY);
	//}
	return true;
}
void Render::RenderThis() {
}
Render::Render(BakaEnvironment *be) {
	this->be = be;
	be->render = this;
}
Render* Render::getRender(BakaEnvironment *be,int state) {
	switch (state) {
		case Render::STATE_ACTIVE: 
			return new SpriteRender(be);
		case Render::STATE_FIXED: 
			return new FixedRender(be);
		default:
			return new Render(be);
	}
}
void SpriteRender::RenderThis() {
	this->be->BeginDraw();
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
			be->RenderSprite(be->thisCam, sprite);
		}
	}
	this->be->EndDraw();
}
void FixedRender::RenderThis() {
	this->be->BeginDraw();
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
		
			be->RenderSpriteGlobal(sprite, sprite->realX, sprite->realY);
		}
	}
	this->be->EndDraw();
}