#include "reflector.h"
Reflector& Reflector::getInstance(){
	static Reflector reflector;
	return reflector;
}
void Reflector::register_class(std::string name, CreateObject className) {
	this->reflectorMap[name] = className;
}
void * Reflector::getClass(std::string name) {
	auto it = reflectorMap.begin();
	it = reflectorMap.find(name);
	if(it==reflectorMap.end()) 
		return nullptr;
	return it->second();
}
