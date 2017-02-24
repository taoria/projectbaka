#include "core\stdafx.h"
#include "render\sprite.h"
#include "algorithm/bmath.h"
//#define A2R(x) (x* math::PI / 180)
#define A2R(x) (x)
SpriteBase::SpriteBase(double x, double y, int sizeX, int sizeY){
	this->realX = x;
	this->realY = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

void SpriteBase::rotation_self(float ang){
	rotation += A2R(ang);
	if (rotation > A2R(360)) rotation -= A2R(360);
	if (rotation < 0) rotation += A2R(360);
}
