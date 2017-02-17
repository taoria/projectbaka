#include "stdafx.h"
#include "master_manager.h"
#include "constant.h"
BaseMap* ConstantManagerBuilder::build_manager(){
	return new ConstantList();
}

BaseMap * MasterManager::NewManager(std::string manager) {
	return nullptr;
}
