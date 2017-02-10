//#pragma once
#include "..\core\bakamain.h"
#include <map>
using namespace std;
class BaseContainer :public ObjectBase
{
private:
	map<b_id,EntityObjectBase*> objectMap;
	int size;
public:
	void PushObject(EntityObjectBase *a);
	void RemoveObject(EntityObjectBase *a);
	int getSize() { return size; }
	EntityObjectBase* GetObjectById(b_id id);
};
class SpriteContainer :public BaseContainer
{

};