#pragma once
#include "bakamain.h"
#include "base_manager.h"
#include "../uncertain/handle_deployer.h"
class ManagerBuilder {
public:
	virtual BaseMap* build_manager() = 0;
};
class ConstantManagerBuilder :public ManagerBuilder {
public:
		virtual BaseMap* build_manager();
};
typedef void* (*CreateObject)(void);
class MasterManager : public ObjectBase, std::map<b_id, BaseMap> {
private:
	BaseMap* NewManager(std::string manager);
public:
	
};