#pragma once
#include <string>
namespace ZG
{
	class IAssetLoader;
	class IAsset;
	class MAIN_API AssetManager :public Singleton<AssetManager>, public GameObjectBase
	{
	public:
		AssetManager();
		~AssetManager();



		//void LoadAsset(string path);
		/*

		*Summary: release asset and associate resource

		*Parameters:

		*     bReleaseResource:if release associate resource


		*Return : void

		*/
		void ReleaseAsset(std::string path, bool bReleaseResource);
		/*

		*Summary: release asset and associate resource

		*Parameters:

		*     path:path of asset

		*	  pArg:addition arg

		*Return : the loaded asset

		*/
		//
		bool	Save(IAsset* pAsset);
		IAsset* LoadAsset(std::string path, void* pArg = nullptr);
		/*

		*Summary: regist loader by suffix

		*Parameters:

		*     strSuff:suffix

		*	  pLoader:บ๓ืบ

		*Return : if exist replace the loader

		*/
		void	AddLoader(std::string strSuff, IAssetLoader* pLoader);
		bool	Init();
		IAsset*	GetAsset(std::string strPath);
	private:
		std::map<std::string, IAssetLoader*> m_LoaderMap;
		std::map<std::string, IAsset*> m_AssetMap;
	};

	extern template class MAIN_API  Singleton < AssetManager > ;
}