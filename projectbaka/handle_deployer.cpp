#include "uncertain/handle_deployer.h"
#include "algorithm/bmath.h"
using namespace IDDeployer;
b_id DeployController::__SearchHandle(){
	return 	this->fixer.GetRandomBID(this->be);
}
IDDeployer::DeployController::DeployController(b_id min, b_id max, BaseMap * baseMap,BakaEnvironment *be) {
	minsize = min; maxsize = max;
	math::Interval<b_id>* temp = new math::Interval<b_id>(min, max, false, false);
	fixer.push_back(temp);
	this->be = be;
	b = baseMap;
}

b_id DeployController::AssignID(){
	b_id freeId = __SearchHandle();
	this->fixer.Split(freeId);
	return freeId;
}

void DeployController::ReforgeHandle(){

	
}

Set<Interval<b_id>*>& IDDeployer::BID_Interval::Split(b_id id) {
	math::Set<math::Interval<b_id>*> *s = new math::Set<math::Interval<b_id>*>;
	if (this->Include(id)) {
		if (id >firstElement) {
			BID_Interval* temp1 = new BID_Interval(firstElement, id - 1);
			s->push_back(temp1);
		}
		if (id <secondElement) {
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

b_id IDDeployer::BID_Interval::GetRandomBID(BakaEnvironment* be) {
	return be->GetRandomInt(this->firstElement, this->secondElement);
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

b_id IDDeployer::BIDSet::GetRandomBID(BakaEnvironment * b) {
	b->GetRandomInt(0, this->size() - 1);
	return dynamic_cast<BID_Interval*>(this)->GetRandomBID(b);
}
