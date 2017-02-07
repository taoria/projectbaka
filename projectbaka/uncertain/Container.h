//#pragma once
#include "core\bakamain.h"
#include <map>
using namespace std;
class BaseContainer
{
private:
	map<b_id,BaseObject*> objectMap;
	int size;
public:
	void PushObject(BaseObject *a);
	void RemoveObject(BaseObject *a);
	int getSize() { return size; }
	BaseObject* GetObjectById(b_id id);
};
class SpriteContainer :public BaseContainer
{

};