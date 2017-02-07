#pragma once
#include<string>
#include<map>
#include "core\bakamain.h"
class BAKADLL Texture {
protected:
	std::string  textureName;
	BakaBitmap *bbmap;
public:
	Texture(std::string tName);
	~Texture();
	BakaBitmap** GetBitmap();
};
class BAKADLL  TextureManager {
public:
	std::map<std::string, Texture*> textureset;
	BakaEnvironment *be;
	Texture* TextureLoadBitmap(PCWSTR adress,std::string picname);
	void TextureDeload(std::string picname);
	TextureManager(BakaEnvironment *be);
	void AttachToSprite(SpriteBase* sprite,std::string name);
};