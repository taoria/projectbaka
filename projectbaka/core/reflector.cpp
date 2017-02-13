#include "reflector.h"

void Reflector::RegisterClass(std::string name, CreateObject className) {
	this->reflectorMap[name] = className;
}
void * Reflector::getClass(std::string name) {
	return nullptr;
}
