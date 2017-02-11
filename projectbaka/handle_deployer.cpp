#include "uncertain/handle_deployer.h"
#include "algorithm/bmath.h"
using namespace IDDeployer;
b_id DeployController::__SearchHandle(){
	return b_id();
}

b_id DeployController::AssignHandle(){
	b_id freeId = __SearchHandle();
	return freeId;
}

void DeployController::ReforgeHandle(){

	
}

Set<Interval<b_id>*>& IDDeployer::BID_Interval::Split(b_id id) {
	math::Set<math::Interval<b_id>*> *s = new math::Set<math::Interval<b_id>*>;
	if (this->Include(id)) {
		if (id - 1>firstElement) {
			BID_Interval* temp1 = new BID_Interval(firstElement, id - 1);
			s->push_back(temp1);
		}
		if (id + 1<secondElement) {
			BID_Interval* temp2 = new BID_Interval(id + 1, secondElement);
			s->push_back(temp2);
		}
		if (s->size() == 0) {
			delete s;
			return *s;
		}
	}
	else {
		delete s;
	}
	return *s;
}
