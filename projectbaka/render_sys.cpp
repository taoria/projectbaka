#include"core/stdafx.h"
#include "core/bakamain.h"
#include "render/sprite.h"
#include "render/render_system.h"
void DebugInt(int x){
	char f[10];
	sprintf_s(f, "%d", x);
}

b_id BaseSystem::ReturnHandleId()
{
	return baseSystemId;
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
bool BakaEnvironment::Render(){
	//if (thisBack->GetColor() == 0){
	//	render_sprite_global(thisBack, 0,0);
	//}
	//for (int i = 0; i <= thisWorld->SIZE; i++){ 
	//	render_sprite(thisCam, thisWorld->render_list[i]);
	//}
	//SpriteBase *s;
	//for (int i = 0; i <= thisGlobal->SIZE; i++){
	//	s = thisGlobal->render_list[i];
	//	render_sprite_global(s,s->realY, s->realY);
	//}
	return true;
}
void Render::render_this() {
}

render_group::~render_group() {
}

Render::Render(BakaEnvironment *be) {
	this->be = be;
	be->render = this;
}
Render* Render::get_render(BakaEnvironment *be,int state) {
	switch (state) {
		case Render::STATE_ACTIVE: 
			return new SpriteRender(be);
		case Render::STATE_FIXED: 
			return new FixedRender(be);
		default:
			return new Render(be);
	}
}
void SpriteRender::render_this() {
	this->be->draw_begin();
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
			be->render_sprite(be->thisCam, sprite);
		}
	}
	this->be->draw_end();
}
void FixedRender::render_this() {
	this->be->draw_begin();
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
		
			be->render_sprite_global(sprite, sprite->realX, sprite->realY);
		}
	}
	this->be->draw_end();
}