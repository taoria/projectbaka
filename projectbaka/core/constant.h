#pragma once
#include "base_object.h"
#include "bakamain.h"
#include "base_manager.h"
//Constant list ,which I pretend to be a manager of constant ,but not yet been used.
class ConstantList:public  BaseMap,std::map<std::string, DWORD> {
private:
	int map_id;
public:
	virtual unsigned int get_id();
};