#pragma once
#include "IAssetLoader.h"
#include "MeshResource.h"
#include "fbxsdk.h"
namespace ZG
{
	class IWorld;
	class Bone;
	class SkeletonResource;
	class RasterMaterial;
	class IWorldObj;
	class MaterialResource;
	class MAIN_API FbxFileLoader :
		public IAssetLoader
	{
	public:



		virtual ~FbxFileLoader()
		{
		}

		virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
	private:
		SmartPointer<IWorldObj> ProcessNode(FbxNode* pNode, string refPath, SmartPointer<IWorldObj> pParent = nullptr, SmartPointer<IWorldObj> pSkeletonObj = nullptr);
		SmartPointer<IWorldObj> ProcessSkeleton(FbxNode* pNode, string refPath, SmartPointer<IWorldObj> pObj = nullptr);
		void		ProcessBone(SmartPointer<SkeletonResource> pRes, Bone* pBone, FbxNode* pObj, int index);
		FbxNode*	GetSkeletonRoot(FbxNode* pNode);
		SmartPointer<MeshResource> ProcessMesh(FbxNode* pMesh, string refPath, SmartPointer<IWorldObj> obj = nullptr, SmartPointer<IWorldObj> pObj = nullptr);
		SmartPointer<RasterMaterial>		ProcessMaterial(FbxSurfaceMaterial* pMat);
		//void LoadPrefab(FbxNode* pNode,IWorld* pWorld);
		FbxFileLoader()
		{
		}
		friend class AssetManager;
		string m_fileDir;
		std::vector<FbxMesh*> vecMeshList;
		std::map<FbxSkeleton*, SmartPointer<SkeletonResource>> m_mapSkeleton;
		std::map<FbxSkeleton*, SmartPointer<IWorldObj>> m_mapSkeObj;
		std::map<FbxSurfaceMaterial*, SmartPointer<MaterialResource>> m_mapMaterial;
	};

}