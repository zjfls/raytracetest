#pragma once

namespace ZG
{
	class IWorldObj;
	class WORLD_API ModuleBase :public GameObjectBase
	{
	public:
		ModuleBase();
		virtual ~ModuleBase();
		virtual void OnAdded(){};
		virtual void OnRemoved(){};
		virtual void Update();
		virtual void OnLateUpdate();
		virtual SmartPointer<ModuleBase> Clone() = 0;



		SmartPointer<IWorldObj> m_pOwnerObj;
		string	m_strName;
		bool	m_bActive;
		bool	m_bTransformUpdated;
	};

}