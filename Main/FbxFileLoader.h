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
	class SkeletonObj;
	class MAIN_API FbxFileLoader :
		public IAssetLoader
	{
	public:



		virtual ~FbxFileLoader()
		{
		}

		virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
	private:
		SmartPointer<IWorldObj> ProcessNode(FbxNode* pNode, SmartPointer<IWorldObj> pParent = nullptr);
		void					ProcessMesh(FbxNode* pNode);
		SmartPointer<IWorldObj> ProcessSkeleton(FbxNode* pNode, SkeletonResource* pRes,SkeletonObj* pObj);
		void		ProcessBone(SmartPointer<SkeletonResource> pRes, Bone* pBone, FbxNode* pFbxObj, int& index, SkeletonObj* pSkeObj);
		FbxNode*	GetSkeletonRoot(FbxNode* pNode);
		SmartPointer<MeshResource> ProcessMeshData(FbxNode* pMesh,  SmartPointer<IWorldObj> obj = nullptr);
		SmartPointer<RasterMaterial>		ProcessMaterial(FbxSurfaceMaterial* pMat, bool bHasSkinInfo);
		void		ProcessAnimation(bool bPerFrame = false);
		void		SetWorldObjPropByFbxNode(IWorldObj* pObj, FbxNode* pFbxObj);
		void		SplitMeshDataByBone();
		void		InitSkeletonCluster(FbxNode* pSkeletonRoot);
		FbxFileLoader()
		{
		}
		void ProcessSkeletonRoot(IWorldObj* pObj);
		void PostProcessSkinMesh(IWorldObj* pRoot);
		friend class AssetManager;
		string m_fileDir;
		std::vector<FbxMesh*> vecMeshList;
		std::map<FbxSkeleton*, SmartPointer<SkeletonResource>> m_mapSkeleton;
		std::map<FbxSkeleton*, SmartPointer<IWorldObj>> m_mapSkeObj;
		std::map<FbxSurfaceMaterial*, SmartPointer<MaterialResource>> m_mapMaterial;
		std::map<SkeletonResource*, std::vector<FbxNode*> > m_SkeletonToFbxNode;
		std::map<SkeletonResource*, SkeletonObj*> m_SkeResToSkeRoot;
		std::map<FbxNode*, IWorldObj*> m_mapFbxToObj;
		std::map<FbxNode*, FbxCluster*> m_NodeToCluster;
		std::string m_strFbxAssetName;
	};

}