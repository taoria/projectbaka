#pragma once
#include "base_manager.h"
#include "../uncertain/handle_deployer.h"
class ManagerBuilder {
public:
	virtual ~ManagerBuilder() = default;
	virtual BaseMap* build_manager() = 0;
	void register_builder(std::string name);
	static void init_base_manager_builder();
};
class ConstantManagerBuilder :public ManagerBuilder {
public:
	BaseMap* build_manager() override;
};
class MasterManager {
private:
	BaseMap* new_manager(std::string manager);
public:
	virtual ~MasterManager() = default;
};