#pragma once


class IWorldObj;
class ModuleBase
{
public:
	ModuleBase();
	virtual ~ModuleBase();
	virtual void Update();
	virtual void OnLateUpdate();




	IWorldObj* m_pOwnerObj;
};

