#pragma once
//#include "bakamain.h"
#include "Container.h"
#include "..\core\base_manager.h"
#include "..\algorithm\bmath.h"
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
	};
	class BIDSet  :Set<Interval<b_id>>{

	};
	class DeployController :public ObjectBase // to calculate a kind of object's size of id;
	{
	private:
		b_id minsize;
		b_id maxsize;
		std::vector<math::Interval<b_id>>  fixer;
		BaseMap *b;
		b_id  __SearchHandle();
	public:
		DeployController(b_id min, b_id max, BaseMap *d) {
			minsize = min; maxsize = max;
			math::Interval<b_id>* temp = new math::Interval<b_id>(min, max, false, false);
			b = d;
		}
		b_id AssignHandle();
		void ReforgeHandle();
	};
}
