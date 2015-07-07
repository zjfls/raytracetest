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
	class SkeletonModule;

	struct MAIN_API FbxLoadOption
	{
		bool m_bExportAnimation;
		FbxLoadOption()
		{
			m_bExportAnimation = false;
		}

	};
	class MAIN_API FbxFileLoader :
		public IAssetLoader
	{
	public:



		virtual ~FbxFileLoader()
		{
		}

		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/);
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
		void		InitSkeletonCluster();
		void		PreGetMesh(FbxNode* pNode);
		FbxNode*	GetWorldNodeByFbxNode(IWorldObj* pObj);
		bool		IsSkeletonMesh(SkeletonResource* pResource, FbxMesh* pMesh);
		FbxFileLoader()
		{
		}
		void ProcessSkeletonRoot(SkeletonModule* pModule, IWorldObj* pMeshObj);
		void PostProcessSkinMesh(IWorldObj* pRoot);
		friend class AssetManager;
		std::string m_fileDir;
		std::string m_exportResDir;
		std::vector<FbxMesh*> vecMeshList;
		std::vector<FbxMesh*> vecDoneMeshList;
		std::map<FbxSkeleton*, SmartPointer<SkeletonResource>> m_mapSkeleton;
		std::map<FbxSkeleton*, SmartPointer<IWorldObj>> m_mapSkeObj;
		std::map<FbxSurfaceMaterial*, SmartPointer<MaterialResource>> m_mapMaterial;
		std::map<SkeletonResource*, std::vector<FbxNode*> > m_SkeletonToFbxNode;
		std::map<SkeletonResource*, SkeletonObj*> m_SkeResToSkeRoot;
		std::map<FbxNode*, IWorldObj*> m_mapFbxToObj;
		std::map<FbxNode*, FbxCluster*> m_NodeToCluster;
		std::string m_strFbxAssetName;

		FbxNode* m_pRootFbxNode;
		FbxLoadOption m_Options;
		//std::vector<FbxMesh*> vecMesh;
	};

}