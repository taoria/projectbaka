#pragma once
#include "bakamain.h"
#include"textureset.h"
class BAKADLL SpriteBase :public BaseObject
{
private:
	int size=0;
	int u_id;
public:
	Texture *spriteTex;
	double realX = 0;
	double realY = 0;
	double sizeX;
	double sizeY;
	bool HaveBitMap;
	SpriteBase() { SpriteBase(0, 0,""); }
	SpriteBase(string textname) {

	}
	SpriteBase(double x, double y, string textname) {

	}
	BakaBitmap* GetBitmap() {
		return *(this->spriteTex->GetBitmap());
	}
};
class UI :public SpriteBase {

};
class SpriteManager {
	
};
class BAKADLL GameBackGround :public SpriteBase
{
public:
	LPCWSTR adress;
	GameBackGround(LPCWSTR  i) :SpriteBase(0, 0,"default_background")
	{	
		adress = i;
	}
	void RenderBackGround()
	{
	}
};
