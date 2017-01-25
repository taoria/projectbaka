#pragma once
#include<string>
#include<map>
#include "bakamain.h"
using namespace std;
class Texture {
protected:
	string textureName;
	BakaBitmap *bbmap;
public:
	Texture(string tName);
	~Texture();
	BakaBitmap** GetBitmap();
};
class  TextureManager {
public:
	map<string, Texture*> textureset;
	BakaEnvironment *be;
	Texture* TextureLoadBitmap(PCWSTR adress,string picname);
	void TextureDeload(string picname);
	TextureManager(BakaEnvironment *be);
};