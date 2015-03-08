#pragma once


class IAssetLoader;
class IAsset;
class AssetManager:public Singleton<AssetManager>
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

	*	  pLoader:บ๓ืบ

	*Return : if exist replace the loader

	*/
	void AddLoader(string strSuff, IAssetLoader* pLoader);
	void Init();
private:
	std::map<string, IAssetLoader*> m_LoaderMap;
	std::map<string, IAsset*> m_AssetMap;
};

