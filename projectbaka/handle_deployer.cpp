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

void IDDeployer::BIDSet::Split(b_id id) {
	BIDSet::iterator i = this->begin();
	for (i; i != this->end(); i++) {
		if ((*i)->Include(id)) {
			break;
		}
	}
	auto set = (*i)->Split(id);
	this->erase(i);
	for (Interval<b_id>* i : *set) {
		this->push_back(i);
	}
	set->clear();
	delete set;
}

void IDDeployer::BIDSet::Merge(Interval<b_id>* m) {
	this->SortIncrease();
	BIDSet *temp = new BIDSet;
	BID_Interval *tempval;
	for (Interval<b_id>* i : *this) {
		tempval = dynamic_cast<BID_Interval*>(&(i->Merge(*m)));
		if (tempval->Invalid()) {
			temp->push_back(i);
		}
		else {
			delete m;
			m = tempval;
		}
	}
	temp->push_back(m);
	*this = *temp;
	temp->clear();
	delete temp;
}
