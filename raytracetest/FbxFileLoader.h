#pragma once
#include "IAssetLoader.h"
#include "MeshResource.h"
class IWorld;

class FbxFileLoader :
	public IAssetLoader
{
public:



	virtual ~FbxFileLoader()
	{
	}

	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
private:
	IWorldObj* ProcessNode(FbxNode* pNode,string refPath,IWorldObj* pParent = nullptr);
	shared_ptr<MeshResource> ProcessMesh(FbxNode* pMesh, string refPath, IWorldObj* obj = nullptr);
	//void LoadPrefab(FbxNode* pNode,IWorld* pWorld);
	FbxFileLoader()
	{
	}
	friend class AssetManager;
};

