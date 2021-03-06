#pragma once
#include<map>
#include "core\bakamain.h"
//texture ,a basic resource of game,to use it ,initialize a texture manager and load texture of picture from disks.
class BAKADLL Texture : public ObjectBase {
protected:
	std::string  textureName;
	BakaBitmap *bbmap;
public:
	Texture(std::string tName);
	~Texture();
	BakaBitmap** get_bitmap();
};
class BAKADLL  TextureManager : public ObjectBase {
public:
	std::map<std::string, Texture*>  textureset;
	BakaEnvironment *be;
	Texture* texture_load_bitmap(PCWSTR adress,std::string picname);
	void texture_deload(std::string picname);
	TextureManager(BakaEnvironment *be);
	void attach_to_sprite(SpriteBase* sprite,std::string name);
};