#include "stdafx.h"
#include "master_manager.h"
#include "constant.h"
std::map<string, ManagerBuilder*> m;
void ManagerBuilder::register_builder(std::string name) {
	m[name] = this;
}

void ManagerBuilder::init_base_manager_builder() {
	ManagerBuilder *temp = new ConstantManagerBuilder();
	temp->register_builder("system_constant_manager");
}
BaseMap* ConstantManagerBuilder::build_manager() {
	return new ConstantList();
}
BaseMap * MasterManager::new_manager(std::string manager) {
	ManagerBuilder *manager_builder = m[manager];
	return manager_builder->build_manager();
}

