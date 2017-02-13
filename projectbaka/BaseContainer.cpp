#include "uncertain\Container.h"
void BaseContainer::PushObject(EntityObjectBase *a){
	if (a != nullptr)
		size++;
		objectMap[a->ReturnHandleId()] = a;
}
void BaseContainer::RemoveObject(EntityObjectBase *a) {
	if (a != nullptr)
		size--;
		objectMap[a->ReturnHandleId()] = nullptr;
}
EntityObjectBase* BaseContainer::GetObjectById(b_id id) {
	return objectMap[id];
}
