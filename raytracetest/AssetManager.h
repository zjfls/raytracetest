#pragma once


class IAssetLoader;
class IAsset;
class AssetManager:public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager();



	void LoadAsset(string path);
	/*

	*Summary: release asset and associate resource

	*Parameters:

	*     bReleaseResource:if release associate resource


	*Return : void

	*/
	void ReleaseAsset(string path,bool bReleaseResource);
	/*

	*Summary: release asset and associate resource

	*Parameters:

	*     path:path of asset

	*	  pArg:addition arg

	*Return : the loaded asset

	*/
	IAsset* LoadAsset(string path,void* pArg = nullptr);
	/*

	*Summary: regist loader by suffix

	*Parameters:

	*     strSuff:suffix

	*	  pLoader:��׺

	*Return : if exist return false,else return true

	*/

	bool AddLoader(string strSuff, IAssetLoader* pLoader);

	std::map<string, IAssetLoader*> m_LoaderMap;
};

