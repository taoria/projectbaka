#pragma once
#include<string>
/**
 * \brief  fundamental base classs ,extended by all the class .
 */
class __declspec(dllexport) ObjectBase {
public:


private:
	virtual std::string ClassName() {
		//return typeid(*this).name;
		return "base_object_rs";
	}
};