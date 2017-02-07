#include "uncertain\handle_deployer.h"
#define MAX_SIZE_BASE 10000
#define MIN_SIZE_BASE 0
void HandleManager::InitHandleManager(){
	globalHandleList = new BaseContainer();
	BaseDeploier = new DeployController(MIN_SIZE_BASE, MAX_SIZE_BASE,globalHandleList);
}
void HandleManager::DeployHandler(BaseObject *a){
	a->setId(BaseDeploier->SearchHandle());
	globalHandleList->PushObject(a);
}
BaseContainer* HandleManager::getGlobalHandleList() {
	return globalHandleList;
}
b_id DeployController::SearchHandle(){
	if (b->GetObjectById(point) == NULL)  return point;
	point = backpoint; //jump to last state;
	for (; b->GetObjectById(point) != 0; ((point++)-minsize)%(maxsize-minsize));
	return point;
}