#include "textureset.h"
#include "stdafx.h"
void texture::TextureLoadBitmap(PCWSTR adress) {
	HRESULT h = be->LoadBitmapFromFile(adress, &bbmap);
}
texture::texture(string tName) {
	texture::textureset[tName] = this;
}