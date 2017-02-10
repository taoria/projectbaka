#pragma once
#include<string>
class ObjectBase {
	virtual std::string ClassName() {
		//return typeid(*this).name;
		return "base_object";
	}
};