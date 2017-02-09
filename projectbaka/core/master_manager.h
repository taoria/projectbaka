#pragma once
#include "bakamain.h"
#include "base_manager.h"
class ManagerBuilder {
public:
	virtual BaseMap BuildManager() = 0;
};
class ConstantManagerBuilder :public ManagerBuilder {
public:
		virtual BaseMap* BuildManager();
};
class MasterManager : public ObjectBase, std::map<int, BaseMap> {
private:

public:
	BaseMap* NewManager(std::string manager);
};