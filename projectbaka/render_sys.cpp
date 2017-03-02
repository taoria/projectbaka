#include"core/stdafx.h"
#include "core/bakamain.h"
#include "render/sprite.h"
#include "render/render_system.h"
void DebugInt(int x){
	char f[10];
	sprintf_s(f, "%d", x);
}

EntityObjectBase::~EntityObjectBase() {
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

void Render::render_this() {
}

render_group::~render_group() {
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
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
			be->render_sprite(be->thisCam, sprite);
		}
	}
}
void FixedRender::render_this() {
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
		
			be->render_sprite_global(sprite, sprite->realX, sprite->realY);
		}
	}
}