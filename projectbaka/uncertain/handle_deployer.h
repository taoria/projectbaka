#pragma once
//#include "bakamain.h"
#include "Container.h"
#include "..\core\base_manager.h"
#include <vector>
#include <utility>
namespace IDDeployer{
	typedef pair<b_id, b_id> interval;
	inline interval newInterval(b_id min,b_id max){
		
	}
	class DeployController :public ObjectBase // to calculate a kind of object's size of id;
	{
	private:
		b_id minsize;
		b_id maxsize;
		std::vector<interval>  fixer;
		BaseMap *b;
		b_id  __SearchHandle();
	public:
		DeployController(b_id min, b_id max, BaseMap *d) {
			minsize = min; maxsize = max;
			fixer.push_back(make_pair(min, max));
			b = d;
		}
		b_id AssignHandle();
		void ReforgeHandle();
	};
}
