#pragma once
#include "bakamain.h"

class BAKADLL SpriteBase :public BaseObject
{
private:
	int size=0;
	int u_id;
public:
	BakaBitmap *SpriteBitmap = NULL;
	double realX = 0;
	double realY = 0;
	double sizeX;
	double sizeY;
	bool HaveBitMap;
	SpriteBase() { SpriteBase(0, 0); }
	SpriteBase(double x, double y){realX = x;realY = y;}
	virtual void RenderSelf(RenderCamera camera);
	virtual void RenderSelf();
};
class UI :public SpriteBase {

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
