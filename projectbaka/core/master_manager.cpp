#include "stdafx.h"
#include "master_manager.h"
#include "constant.h"
BaseMap* ConstantManagerBuilder::BuildManager(){
	return new ConstantList();
}

BaseMap * MasterManager::NewManager(std::string manager) {
	return nullptr;
}
