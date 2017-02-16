

#include "core/stdafx.h"
#include "render/textureset.h"
#include "render/sprite.h"
using namespace std;
Texture* TextureManager::TextureLoadBitmap(PCWSTR adress,string newTextureName) {
	Texture *temp = new Texture(newTextureName);
	HRESULT h = be->LoadBitmapFromFile(adress, temp->get_bitmap());
	textureset[newTextureName] = temp;
	return temp;
}
BakaBitmap** Texture::get_bitmap() {
	return &bbmap;
}
Texture::Texture(string tName) {
	this->textureName = tName;
}
Texture::~Texture() {
	this->bbmap->Release();
}
void TextureManager::texture_deload(string textureName) {
	Texture *temp = textureset[textureName];
	textureset.erase(textureName);
	temp->~Texture();
}
TextureManager::TextureManager(BakaEnvironment *be) {
	this->be = be;
}
void TextureManager::attach_to_sprite(SpriteBase* base,std::string  name) {
	base->spriteTex = this->textureset[name];
}