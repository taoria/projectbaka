
#include "Container.h"
void BaseContainer::PushObject(BaseObject *a){
	if (a != NULL)
		size++;
		objectMap[a->ReturnHandleId()] = a;
}
void BaseContainer::RemoveObject(BaseObject *a) {
	if (a != NULL)
		size--;
		objectMap[a->ReturnHandleId()] = NULL;
}
BaseObject* BaseContainer::GetObjectById(b_Handle id) {
	return objectMap[id];
}
