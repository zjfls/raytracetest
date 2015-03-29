#pragma once


class IWorldObj;
class WORLD_API ModuleBase
{
public:
	ModuleBase();
	virtual ~ModuleBase();
	virtual void OnAdded(){};
	virtual void OnRemoved(){};
	virtual void Update();
	virtual void OnLateUpdate();
	virtual ModuleBase* Clone() = 0;



	IWorldObj* m_pOwnerObj;
	string m_strName;
};

