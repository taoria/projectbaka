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
		Set<Interval<b_id>*>& split(b_id id);
		BID_Interval(b_id left, b_id right);
		b_id get_random_bid(BakaEnvironment *b);
	};
	class BIDSet  :public Set<Interval<b_id>*>{
	public:
		void split(b_id id);
		void merge(Interval<b_id>*);
		b_id get_random_bid(BakaEnvironment *b);
	

	};
	class DeployController :public ObjectBase // to calculate a kind of object's size of id;
	{
	private:
		BakaEnvironment *be;
		b_id minsize;
		b_id maxsize;
		BIDSet  fixer;
		BaseMap *b;
		b_id  __search_handle();
	public:
		DeployController(b_id min, b_id max, BaseMap *d, BakaEnvironment *be);
		b_id assign_id();
		void reforge_handle();
	};
}
