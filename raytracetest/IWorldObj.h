#pragma once
#include "ObjComponent.h"
#include "ModuleBase.h"
#include "LightBase.h"
#include "Transform.h"
class IRenderable;
class IWorldObj
{
public:
	IWorldObj();
	virtual ~IWorldObj();
	virtual bool addChild(IWorldObj* pObj);
	virtual bool removeChild(IWorldObj* pObj);
	//virtual bool addModule(ModuleBase* pModule);
	virtual bool removeModule(ModuleBase* pModule);


	template<class T>
	T* addModule()
	{
		T* pModule = new T;
		pModule->m_pOwnerObj = this;
		m_vecModules.push_back(pModule);
		return pModule;
	};
	virtual void Update();

	template<class T>
	void GetAllModuleRecursive(std::vector<T*>& vecResults);
	void GetRenderableRecursive(std::vector<IRenderable*>& vecRenderabls);
	//bool addComponent(ObjComponent* pComponent);
///////////////////////////////////
	Transform*					m_pTransform;
private:
	IWorldObj*					m_pParent;
	std::vector<IWorldObj*>		m_vecChildren;
	std::vector<ModuleBase*>	m_vecModules;


	friend class Transform;
};

template<class T>
void IWorldObj::GetAllModuleRecursive(std::vector<T*>& vecResults)
{
	for each (ModuleBase*  var in m_vecModules)
	{
		T* pModule = dynamic_cast<T*>(var);
		if (pModule != nullptr)
		{
			vecResults.push_back(pModule);
		}
	}
	for each (IWorldObj* var in m_vecChildren)
	{
		var->GetAllModuleRecursive<T>(vecResults);
	}
}

