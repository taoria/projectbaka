#pragma once
//#include "bakamain.h"
#include "Container.h"
class DeployController :public ObjectBase // to calculate a kind of object's size of id;
{
private:
	b_id minsize;
	b_id maxsize;
	b_id point;
	b_id backpoint;
	BaseContainer *b;
public:
	b_id  SearchHandle();
	DeployController(b_id min, b_id max,BaseContainer *d)
	{
		minsize = min; maxsize = max;
		point = min; backpoint = min;
		b = d;
	}


};
DeployController *BaseDeploier;
class HandleManager
{
private:
	 static  BaseContainer *globalHandleList;
	static DeployController *BaseDeploier;
public:

	static void DeployHandler(EntityObjectBase *a);
	static void InitHandleManager();
	static BaseContainer* getGlobalHandleList();
};
BaseContainer *HandleManager::globalHandleList = NULL;
DeployController *HandleManager::BaseDeploier = NULL;