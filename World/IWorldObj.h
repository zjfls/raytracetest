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
	virtual bool	addChild(IWorldObj* pObj);
	virtual bool	removeChild(IWorldObj* pObj);
	virtual bool	removeModule(ModuleBase* pModule);
	unsigned int	GetChildCount() const;
	IWorldObj*		GetChild(int i) const;
	virtual IWorldObj* Clone(bool bRecursive);

	template<class T>
	T* addModule()
	{
		T* pModule = new T;
		pModule->m_pOwnerObj = this;
		m_vecModules.push_back(pModule);
		pModule->OnAdded();
		return pModule;
	};
	virtual void Update();

	template<class T>
	void GetAllModuleRecursive(std::vector<T*>& vecResults);
	void GetRenderableRecursive(std::vector<IRenderable*>& vecRenderabls);
	/////////////////////////////////////////////////////
	unsigned int	 GetModuleCount()	const;
	ModuleBase*	GetModule(int i) const;

	template<class T>
	bool		IsHaveModule(T* module);
	template<class T>
	bool		IsHaveModule();


	//virtual IWorldObj* Clone(bool bRecursive);

private:
	IWorldObj*					m_pParent;
	std::vector<IWorldObj*>		m_vecChildren;
	std::vector<ModuleBase*>	m_vecModules;
public:
	string						m_strName;
	///////////////////////////////////
	Transform*					m_pTransform;
	friend class Transform;
};

template<class T>
bool IWorldObj::IsHaveModule()
{
	for each (ModuleBase* var in m_vecModules)
	{
		T* pModule = dynamic_cast<T*>(var);
		if (pModule != false)
		{
			return true;
		}
	}
	return false;
}

template<class T>
bool IWorldObj::IsHaveModule(T* module)
{
	for each (ModuleBase* var in m_vecModules)
	{
		T* pModule = dynamic_cast<T*>(var);
		if (pModule == module)
		{
			return true;
		}
	}
	return false;
}

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

