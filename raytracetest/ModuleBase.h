#pragma once


class IWorldObj;
class ModuleBase
{
public:
	ModuleBase();
	virtual ~ModuleBase();
	virtual void OnAdded(){};
	virtual void OnRemoved(){};
	virtual void Update();
	virtual void OnLateUpdate();




	IWorldObj* m_pOwnerObj;
	string m_strName;
};

