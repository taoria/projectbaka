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
	SpriteBase() { SpriteBase(0, 0); }
	SpriteBase(double x, double ye) {

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
	GameBackGround(LPCWSTR  i) :SpriteBase(0, 0)
	{	
		adress = i;
	}
	void RenderBackGround()
	{
	}
};
