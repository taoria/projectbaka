#include "uncertain/handle_deployer.h"
#include "algorithm/bmath.h"
using namespace IDDeployer;
b_id DeployController::__search_handle(){
	return 	this->fixer.get_random_bid(this->be);
}
IDDeployer::DeployController::DeployController(b_id min, b_id max, BaseMap * baseMap,BakaEnvironment *be) {
	minsize = min; maxsize = max;
	math::Interval<b_id>* temp = new math::Interval<b_id>(min, max, false, false);
	fixer.push_back(temp);
	this->be = be;
	b = baseMap;
}

b_id DeployController::assign_id(){
	b_id freeId = __search_handle();
	this->fixer.split(freeId);
	return freeId;
}

void DeployController::reforge_handle(){

	
}

Set<Interval<b_id>*>& IDDeployer::BID_Interval::split(b_id id) {
	Set<math::Interval<b_id>*> *s = new math::Set<math::Interval<b_id>*>;
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

IDDeployer::BID_Interval::BID_Interval(b_id left, b_id right):math::Interval<unsigned>(left,right){
}
b_id IDDeployer::BID_Interval::get_random_bid(BakaEnvironment* be) {
	return be->get_random_int(this->firstElement, this->secondElement);
}

void IDDeployer::BIDSet::split(b_id id) {
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

void IDDeployer::BIDSet::merge(Interval<b_id>* m) {
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

b_id IDDeployer::BIDSet::get_random_bid(BakaEnvironment * b) {
	b->get_random_int(0, this->size() - 1);
	return dynamic_cast<BID_Interval*>(this)->get_random_bid(b);
}
