#pragma once
#include<string>
#include<map>
typedef void* (*CreateObject)(void);
//the reflector! but I did not wanna write it any more ,for it's too much work to be done.
class Reflector {
private:
	std::map < std::string, CreateObject> reflectorMap;
public:
	static Reflector& getInstance();
	void register_class(std::string name, CreateObject classObject);
	void* getClass(std::string name);
};