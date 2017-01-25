
#include "stdafx.h"
#include "textureset.h"
Texture* TextureManager::TextureLoadBitmap(PCWSTR adress,string newTextureName) {
	Texture *temp = new Texture(newTextureName);
	HRESULT h = be->LoadBitmapFromFile(adress, temp->GetBitmap());
	textureset[newTextureName] = temp;
	return temp;
}
BakaBitmap** Texture::GetBitmap() {
	return &bbmap;
}
Texture::Texture(string tName) {
	this->textureName = tName;
}
Texture::~Texture() {
	this->bbmap->Release();
}
void TextureManager::TextureDeload(string textureName) {
	Texture *temp = textureset[textureName];
	textureset.erase(textureName);
	temp->~Texture();
}
TextureManager::TextureManager(BakaEnvironment *be) {
	this->be = be;
}