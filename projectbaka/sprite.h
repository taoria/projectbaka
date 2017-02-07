#pragma once
#include "bakamain.h"
#include"textureset.h"
class BAKADLL SpriteBase :public BaseObject
{
private:
	int size=0;
	int u_id;
	float rotation=0;
public:
	Texture *spriteTex;
	double realX = 0;
	double realY = 0;
	int sizeX =-1;
	int sizeY =-1;
	bool HaveBitMap;
	SpriteBase() { SpriteBase(0, 0); }
	SpriteBase(double x, double ye) {
	}
	SpriteBase(double x, double y, int sizeX, int sizeY);
	void Rotation(float ang);
	float GetRotation() {
		return rotation;
	}
	void ResetRotation() {
		rotation = 0;
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
