#pragma once
#include"bakamain.h"
// base map to manager games object 
class BaseMap :public ObjectBase {
public:
	virtual unsigned int get_id() = 0;
};