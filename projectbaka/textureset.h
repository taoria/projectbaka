#pragma once
#include<string>
#include<map>
#include "bakamain.h"
using namespace std;
class texture {
public:
	static map<string, texture*> textureset;
	static BakaEnvironment *be;
	BakaBitmap *bbmap;
	texture(string tName);
	void TextureLoadBitmap(PCWSTR adress);
};