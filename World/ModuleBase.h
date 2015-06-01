#pragma once


class IWorldObj;
class WORLD_API ModuleBase:public GameObjectBase
{
public:
	ModuleBase();
	virtual ~ModuleBase();
	virtual void OnAdded(){};
	virtual void OnRemoved(){};
	virtual void Update(SmartPointer<ModuleBase> pModule);
	virtual void OnLateUpdate(SmartPointer<ModuleBase> pModule);
	virtual SmartPointer<ModuleBase> Clone() = 0;



	SmartPointer<IWorldObj> m_pOwnerObj;
	string m_strName;
};

