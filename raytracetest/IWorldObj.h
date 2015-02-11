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


	//bool addComponent(ObjComponent* pComponent);
///////////////////////////////////
	Transform* m_pTransform;
	std::vector<IWorldObj*> m_vecChildren;
	std::vector<ModuleBase*> m_vecModules;
};

