#include "uncertain\Container.h"
void BaseContainer::PushObject(EntityObjectBase *a){
	if (a != NULL)
		size++;
		objectMap[a->ReturnHandleId()] = a;
}
void BaseContainer::RemoveObject(EntityObjectBase *a) {
	if (a != NULL)
		size--;
		objectMap[a->ReturnHandleId()] = NULL;
}
EntityObjectBase* BaseContainer::GetObjectById(b_id id) {
	return objectMap[id];
}
