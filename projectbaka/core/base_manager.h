#pragma once
#include"bakamain.h"
class BaseMap :public ObjectBase {
public:
	virtual unsigned int GetId() = 0;
};