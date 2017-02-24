#pragma once
#include<string>
class __declspec(dllexport) ObjectBase {
public:


private:
	virtual std::string ClassName() {
		//return typeid(*this).name;
		return "base_object_rs";
	}
};