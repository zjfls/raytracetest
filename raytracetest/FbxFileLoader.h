#pragma once
#include "IAssetLoader.h"
#include "MeshResource.h"
class IWorld;
class Bone;
class SkeletonResource;
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
	IWorldObj* ProcessSkeleton(FbxNode* pNode, string refPath, IWorldObj* pParent = nullptr);
	void		ProcessBone(shared_ptr<SkeletonResource> pRes, Bone* pBone, FbxNode* pObj, int index);
	FbxNode*	GetSkeletonRoot(FbxNode* pNode);
	shared_ptr<MeshResource> ProcessMesh(FbxNode* pMesh, string refPath, IWorldObj* obj = nullptr);
	//void LoadPrefab(FbxNode* pNode,IWorld* pWorld);
	FbxFileLoader()
	{
	}
	friend class AssetManager;
	string m_fileDir;
	std::vector<FbxMesh*> vecMeshList;
	std::map<FbxSkeleton*,shared_ptr<SkeletonResource>> m_mapSkeleton;
};

