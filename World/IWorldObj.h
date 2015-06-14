#pragma once
#include "ModuleBase.h"
#include "LightBase.h"
#include "Transform.h"
namespace ZG
{
	class IRenderable;
	class WORLD_API IWorldObj :public GameObjectBase
	{
	public:
		IWorldObj();
		virtual ~IWorldObj();
		virtual bool	addChild(SmartPointer<IWorldObj> pObj);
		virtual bool	removeChild(SmartPointer<IWorldObj> pObj);
		virtual bool	removeAllChildren();
		virtual bool	removeModule(SmartPointer<ModuleBase> pModule);
		unsigned int	GetChildCount() const;
		IWorldObj*		GetParent(){ return m_pParent; }
		SmartPointer<IWorldObj>		GetChild(unsigned int i) const;
		virtual SmartPointer<IWorldObj> Clone(bool bRecursive);

		template<class T>
		SmartPointer<T> addModule()
		{
			SmartPointer<T> pModule = SmartPointer<T>(new T);
			pModule->m_pOwnerObj = this;
			m_vecModules.push_back(pModule.SmartPointerCast<ModuleBase>());
			pModule->OnAdded();
			return pModule;
		};
		virtual void Update();
		virtual void AfterUpdate();

		template<class T>
		void GetAllModuleRecursive(std::vector<SmartPointer<T>>& vecResults);
		template<class T>
		void GetAllModule(std::vector<SmartPointer<T>>& vecResults);
		void GetRenderableRecursive(std::vector<SmartPointer<IRenderable>>& vecRenderabls);
		/////////////////////////////////////////////////////
		unsigned int	 GetModuleCount()	const;
		SmartPointer<ModuleBase>	GetModule(int i) const;

		template<class T>
		bool		IsHaveModule(SmartPointer<T> module);
		template<class T>
		bool		IsHaveModule();

		//static SmartPointer<IWorldObj> new IWorldObj
		//{
		//	SmartPointer<IWorldObj> pObj(new IWorldObj);
		//	
		//	//pObj->m_pTransform = pObj->addModule<Transform>();
		//	return pObj;
		//}
		//virtual IWorldObj* Clone(bool bRecursive);

		protected:
		//SmartPointer<IWorldObj>					
		IWorldObj*								m_pParent;
		std::vector<SmartPointer<IWorldObj>>		m_vecChildren;
		std::vector<SmartPointer<ModuleBase>>	m_vecModules;
	public:
		string						m_strName;
		///////////////////////////////////
		SmartPointer<Transform>					m_pTransform;
		friend class Transform;
	};

	template<class T>
	void ZG::IWorldObj::GetAllModule(std::vector<SmartPointer<T>>& vecResults)
	{
		for each (SmartPointer<ModuleBase>  var in m_vecModules)
		{
			SmartPointer<T> pModule = var.SmartPointerCast<T>();
			if (pModule != nullptr)
			{
				vecResults.push_back(pModule);
			}
		}
	}

	template<class T>
	bool IWorldObj::IsHaveModule()
	{
		for each (SmartPointer<ModuleBase> var in m_vecModules)
		{
			SmartPointer<T> pModule = dynamic_pointer_cast<T>(var);
			if (pModule != false)
			{
				return true;
			}
		}
		return false;
	}

	template<class T>
	bool IWorldObj::IsHaveModule(SmartPointer<T> module)
	{
		for each (SmartPointer<ModuleBase> var in m_vecModules)
		{
			SmartPointer<T> pModule = var.SmartPointerCast<T>();
			if (pModule == module)
			{
				return true;
			}
		}
		return false;
	}

	template<class T>
	void IWorldObj::GetAllModuleRecursive(std::vector<SmartPointer<T>>& vecResults)
	{
		for each (SmartPointer<ModuleBase>  var in m_vecModules)
		{
			SmartPointer<T> pModule = var.SmartPointerCast<T>();
			if (pModule != nullptr)
			{
				vecResults.push_back(pModule);
			}
		}
		for each (SmartPointer<IWorldObj> var in m_vecChildren)
		{
			var->GetAllModuleRecursive<T>(vecResults);
		}
	}

}