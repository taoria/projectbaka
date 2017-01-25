#pragma once
//#include "bakamain.h"
#include "Container.h"
class DeployController // to calculate a kind of object's size of id;
{
private:
	b_Handle minsize;
	b_Handle maxsize;
	b_Handle point;
	b_Handle backpoint;
	BaseContainer *b;
public:
	b_Handle  SearchHandle();
	DeployController(b_Handle min, b_Handle max,BaseContainer *d)
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

	static void DeployHandler(BaseObject *a);
	static void InitHandleManager();
	static BaseContainer* getGlobalHandleList();
};
BaseContainer *HandleManager::globalHandleList = NULL;
DeployController *HandleManager::BaseDeploier = NULL;