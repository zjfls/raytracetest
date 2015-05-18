#pragma once
#include "ModuleBase.h"
#include "LightBase.h"
#include "Transform.h"
class IRenderable;
class WORLD_API IWorldObj
{
public:
	IWorldObj();
	virtual ~IWorldObj();
	virtual bool	addChild(shared_ptr<IWorldObj> pObj);
	virtual bool	removeChild(shared_ptr<IWorldObj> pObj);
	virtual bool	removeModule(shared_ptr<ModuleBase> pModule);
	unsigned int	GetChildCount() const;
	shared_ptr<IWorldObj>		GetChild(unsigned int i) const;
	virtual shared_ptr<IWorldObj> Clone(bool bRecursive);

	template<class T>
	shared_ptr<T> addModule(shared_ptr<IWorldObj> pObj)
	{
		shared_ptr<T> pModule = shared_ptr<T>(new T);
		pModule->m_pOwnerObj = pObj;
		m_vecModules.push_back(pModule);
		pModule->OnAdded();
		return pModule;
	};
	virtual void Update();
	virtual void AfterUpdate();

	template<class T>
	void GetAllModuleRecursive(std::vector<shared_ptr<T>>& vecResults);
	void GetRenderableRecursive(std::vector<shared_ptr<IRenderable>>& vecRenderabls);
	/////////////////////////////////////////////////////
	unsigned int	 GetModuleCount()	const;
	shared_ptr<ModuleBase>	GetModule(int i) const;

	template<class T>
	bool		IsHaveModule(shared_ptr<T> module);
	template<class T>
	bool		IsHaveModule();

	static shared_ptr<IWorldObj> CreateWorldObj()
	{
		shared_ptr<IWorldObj> pObj(new IWorldObj);
		
		pObj->m_pTransform = pObj->addModule<Transform>(pObj);
		return pObj;
	}
	//virtual IWorldObj* Clone(bool bRecursive);

private:
	//shared_ptr<IWorldObj>					
	IWorldObj*								m_pParent;
	std::vector<shared_ptr<IWorldObj>>		m_vecChildren;
	std::vector<shared_ptr<ModuleBase>>	m_vecModules;
public:
	string						m_strName;
	///////////////////////////////////
	shared_ptr<Transform>					m_pTransform;
	friend class Transform;
};

template<class T>
bool IWorldObj::IsHaveModule()
{
	for each (shared_ptr<ModuleBase> var in m_vecModules)
	{
		shared_ptr<T> pModule = dynamic_pointer_cast<T>(var);
		if (pModule != false)
		{
			return true;
		}
	}
	return false;
}

template<class T>
bool IWorldObj::IsHaveModule(shared_ptr<T> module)
{
	for each (shared_ptr<ModuleBase> var in m_vecModules)
	{
		shared_ptr<T> pModule = dynamic_pointer_cast<T>(var);
		if (pModule == module)
		{
			return true;
		}
	}
	return false;
}

template<class T>
void IWorldObj::GetAllModuleRecursive(std::vector<shared_ptr<T>>& vecResults)
{
	for each (shared_ptr<ModuleBase>  var in m_vecModules)
	{
		shared_ptr<T> pModule = dynamic_pointer_cast<T>(var);
		if (pModule != nullptr)
		{
			vecResults.push_back(pModule);
		}
	}
	for each (shared_ptr<IWorldObj> var in m_vecChildren)
	{
		var->GetAllModuleRecursive<T>(vecResults);
	}
}

