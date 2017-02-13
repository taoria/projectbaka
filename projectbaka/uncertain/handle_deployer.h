#pragma once
//#include "bakamain.h"
#include "Container.h"
#include "../core/base_manager.h"
#include "../algorithm/bmath.h"
#include <vector>
#include <utility>
using math::Interval;
using math::Set;
namespace IDDeployer {
	class BID_Interval :public Interval<b_id> {
	public:
		Set<Interval<b_id>*>& Split(b_id id);
		BID_Interval(b_id left, b_id right) :math::Interval<b_id>(left,right){

		}
		b_id GetRandomBID(BakaEnvironment *b);
	};
	class BIDSet  :public Set<Interval<b_id>*>{
	public:
		void Split(b_id id);
		void Merge(Interval<b_id>*);
		b_id GetRandomBID(BakaEnvironment *b);

	};
	class DeployController :public ObjectBase // to calculate a kind of object's size of id;
	{
	private:
		BakaEnvironment *be;
		b_id minsize;
		b_id maxsize;
		BIDSet  fixer;
		BaseMap *b;
		b_id  __SearchHandle();
	public:
		DeployController(b_id min, b_id max, BaseMap *d, BakaEnvironment *be);
		b_id AssignID();
		void ReforgeHandle();
	};
}
