#pragma once
#include "Singleton.h"
#include <string>
namespace ZG
{ 
	class IWorldObj;
	struct stPrefabInfo
	{
		stPrefabInfo()
		{
			m_pRoot = nullptr;
			m_strPrefabRes = "";
			m_bIsRoot = false;
		}
		IWorldObj* m_pRoot;
		bool		m_bIsRoot;
		std::string m_strPrefabRes;
	};
	class EDITOR_API ScenePrefabManager:public Singleton<ScenePrefabManager>
	{
	public:
		ScenePrefabManager();
		virtual ~ScenePrefabManager();

		void	OnAddPrefabRes(IWorldObj* pObj, std::string);
		void	Clear();

		std::map<IWorldObj*, stPrefabInfo> m_MapPrefabInfo;
	};
	extern template  class EDITOR_API  Singleton < ScenePrefabManager >;
}


