#pragma once
#include<string>
#include<map>
typedef void* (*CreateObject)(void);
class Reflector {
private:
	std::map < std::string, CreateObject> reflectorMap;
public:
	static Reflector& getInstance();
	void RegisterClass(std::string name, CreateObject classObject);
	void* getClass(std::string name);
};