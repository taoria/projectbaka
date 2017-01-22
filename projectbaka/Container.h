//#pragma once
#include "bakamain.h"
#include <map>
using namespace std;
class BaseContainer
{
private:
	map<b_Handle,BaseObject*> objectMap;
	int size;
public:
	void PushObject(BaseObject *a);
	void RemoveObject(BaseObject *a);
	int getSize() { return size; }
	BaseObject* GetObjectById(b_Handle id);
};
class SpriteContainer :public BaseContainer
{

};