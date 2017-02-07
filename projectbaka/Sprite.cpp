#include "stdafx.h"
#include "sprite.h"

SpriteBase::SpriteBase(double x, double y, int sizeX, int sizeY){
	this->realX = x;
	this->realY = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

void SpriteBase::Rotation(float ang){
	rotation += ang;
}
