#include "uncertain\Container.h"
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
BaseObject* BaseContainer::GetObjectById(b_id id) {
	return objectMap[id];
}
