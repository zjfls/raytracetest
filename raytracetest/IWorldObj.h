#pragma once
#include "ObjComponent.h"
#include "ModuleBase.h"
class IWorldObj
{
public:
	IWorldObj();
	virtual ~IWorldObj();
	virtual bool addChild(IWorldObj* pObj);
	virtual bool removeChild(IWorldObj* pObj);
	virtual bool addModule(ModuleBase* pModule);
	virtual bool removeModule(ModuleBase* pModule);
	virtual void Update();

	//bool addComponent(ObjComponent* pComponent);
///////////////////////////////////
	Transform*					m_pTransform;
	IWorldObj*					m_pParent;
	std::vector<IWorldObj*>		m_vecChildren;
	std::vector<ModuleBase*>	m_vecModules;
};

