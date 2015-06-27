#pragma once

namespace ZG
{
	class IWorldObj;
	class MAIN_API ModuleBase :public GameObjectBase
	{
	public:
		ModuleBase();
		virtual ~ModuleBase();
		void		Added();
		void		Removed();
		void		Update();
		void		SetActive(bool bActive);
		bool		IsActive();
		virtual SmartPointer<ModuleBase> Clone() = 0;
	protected:
		virtual void OnAdded(){};
		virtual void OnRemoved(){};
		virtual void OnInitialize(){};
		virtual void OnUpdate(){};
		virtual void OnLateUpdate(){};
		virtual void OnStart(){};
		virtual void OnActive(){};
		virtual void OnDeactive(){};

		



		bool	m_bActive;
	private:
		bool	m_bInitialized;
		bool	m_bStarted;
		
	public:
		IWorldObj* m_pOwnerObj;
		string	m_strName;
		bool	m_bTransformUpdated;
		friend class IWorldObj;
	};

}