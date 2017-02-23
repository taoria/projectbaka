#pragma once
#include<string>
class __declspec(dllexport) ObjectBase {
	virtual std::string ClassName() {
		//return typeid(*this).name;
		return "base_object_rs";
	}
};