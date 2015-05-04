#pragma once


class IWorldObj;
class WORLD_API ModuleBase
{
public:
	ModuleBase();
	virtual ~ModuleBase();
	virtual void OnAdded(){};
	virtual void OnRemoved(){};
	virtual void Update(std::shared_ptr<ModuleBase> pModule);
	virtual void OnLateUpdate(std::shared_ptr<ModuleBase> pModule);
	virtual shared_ptr<ModuleBase> Clone() = 0;



	shared_ptr<IWorldObj> m_pOwnerObj;
	string m_strName;
};

