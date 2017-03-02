#pragma once
#include "base_manager.h"
#include "../uncertain/handle_deployer.h"
//ManagerBuilder  a Manager Builder could Builder Managers of all types ,not yet been used and i don't know whether it works
class ManagerBuilder {
public:
	virtual ~ManagerBuilder() = default;
	virtual BaseMap* build_manager() = 0;
	void register_builder(std::string name);
	static void init_base_manager_builder();
};
//Constant Mananger Builder is Manager Builder build Constant List
class ConstantManagerBuilder :public ManagerBuilder {
public:
	BaseMap* build_manager() override;
};
//While MasterManager is a manager to manage mangaers
class MasterManager {
private:
	BaseMap* new_manager(std::string manager);
public:
	virtual ~MasterManager() = default;
};