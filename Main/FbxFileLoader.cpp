#include "stdafx.h"
#include "FbxFileLoader.h"
#include "FbxAsset.h"
#include "FbxAppManager.h"
#include "ResourceManager.h"
#include "MeshResource.h"
#include "Mesh.h"
#include "PrefabResource.h"
#include "FilePath.h"
#include "SkeletonResource.h"
#include "RasterMaterial.h"
#include "skeleton.h"
#include "MaterialArg.h"
#include "TextureSampler.h"
#include "Texture2D.h"
#include "RenderEnum.h"
#include "Transform.h"
#include "IWorldObj.h"
#include "ResDef.h"
#include "FileOperation.h"
#include <io.h>
#include "VertexShader.h"
#include "FragShader.h"
#include "MaterialPass.h"
#include "AssetManager.h"
#include "SkeletonObj.h"
#include "skeleton.h"
#include "AnimationCurve.h"
#include "AnimationResource.h"
#include "AnimationAsset.h"
#include "AnimationAssetLoader.h"
#include "StrUtil.h"
#include "AnimationTrack.h"
#include "XmlPrefabLoader.h"
#include "PrefabResource.h"
#include "PrefabAsset.h"
#include <direct.h>
//
IAsset* FbxFileLoader::Load(std::string path, void* pArg /*= nullptr*/)
{
	//std::vector<FbxMesh*> vecMeshList;
	//std::vector<FbxMesh*> vecDoneMeshList;
	//std::map<FbxSkeleton*, SmartPointer<SkeletonResource>> m_mapSkeleton;
	//std::map<FbxSkeleton*, SmartPointer<IWorldObj>> m_mapSkeObj;
	//std::map<FbxSurfaceMaterial*, SmartPointer<MaterialResource>> m_mapMaterial;
	//std::map<SkeletonResource*, std::vector<FbxNode*> > m_SkeletonToFbxNode;
	//std::map<SkeletonResource*, SkeletonObj*> m_SkeResToSkeRoot;
	//std::map<FbxNode*, IWorldObj*> m_mapFbxToObj;
	//std::map<FbxNode*, FbxCluster*> m_NodeToCluster;
	//std::string m_strFbxAssetName;

	//FbxNode* m_pRootFbxNode;
	if (pArg != nullptr)
	{
		m_Options = *((FbxLoadOption*)pArg);
	}


	vecMeshList.clear();
	vecDoneMeshList.clear();
	m_mapSkeleton.clear();
	m_mapSkeObj.clear();
	m_mapMaterial.clear();
	m_SkeletonToFbxNode.clear();
	m_SkeResToSkeRoot.clear();
	m_mapFbxToObj.clear();
	m_NodeToCluster.clear();
	m_pRootFbxNode = nullptr;
	
	m_fileDir = getFileDirectory(path);
	m_strFbxAssetName = getFileName(path);
	m_strFbxAssetName = removeSuffix(m_strFbxAssetName);
	m_exportResDir = m_fileDir + "/" + m_strFbxAssetName + "/";
	FbxAsset* pAsset = new FbxAsset;
	m_pAsset = pAsset;
	pAsset->m_strPath = path;
	pAsset->m_pFbxScene = FbxScene::Create(FbxAppManager::GetInstance()->m_pFbxSdkManager, path.c_str());
	pAsset->m_pFbxScene->Clear();
	//
	FbxImporter* pImporter = FbxImporter::Create(FbxAppManager::GetInstance()->m_pFbxSdkManager, "importer");
	const char* fileName = path.c_str();

	bool bImportStatus = pImporter->Initialize(fileName, -1, FbxAppManager::GetInstance()->m_pFbxSdkManager->GetIOSettings());
	int nFileMajor, nFileMinor, nFileRevision;
	pImporter->GetFileVersion(nFileMajor, nFileMinor, nFileRevision);
	//bool bImportStatus = pImporter->Initialize(fileName, -1, m_pFbxSdkManager->GetIOSettings());
	if (bImportStatus == false)
	{
		return pAsset;
	}
	bImportStatus = pImporter->Import(pAsset->m_pFbxScene);
	pImporter->Destroy();


	//
	FbxSystemUnit SceneSystemUnit = pAsset->m_pFbxScene->GetGlobalSettings().GetSystemUnit();
	//if (SceneSystemUnit.GetScaleFactor() != 1.0)
	//{
	//	// センチメーター単位にコンバートする
	//	FbxSystemUnit::cm.ConvertScene(pAsset->m_pFbxScene);
	//}
	//
	FbxAxisSystem SceneAxisSystem = pAsset->m_pFbxScene->GetGlobalSettings().GetAxisSystem();
	int sign = 1;
	FbxAxisSystem::EUpVector upvec = SceneAxisSystem.GetUpVector(sign);
	if (SceneAxisSystem != FbxAxisSystem::DirectX)
	{

		FbxAxisSystem directXAxisSys(upvec,
			FbxAxisSystem::EFrontVector::eParityOdd,
			FbxAxisSystem::eLeftHanded);

		//FbxAxisSystem::DirectX.ConvertScene(pAsset->m_pFbxScene);
		directXAxisSys.ConvertScene(pAsset->m_pFbxScene);
	}
	//
	FbxNode* pRootNode = pAsset->m_pFbxScene->GetRootNode();
	m_pRootFbxNode = pRootNode;
	if (pRootNode == nullptr)
	{
		return pAsset;
	}
	PreGetMesh(pRootNode);
	InitSkeletonCluster();
	SmartPointer<IWorldObj> pRoot = ProcessNode(pRootNode, nullptr);
	m_mapFbxToObj[pRootNode] = pRoot.get();
	ProcessMesh(pRootNode);
	PostProcessSkinMesh(pRoot.get());


	ProcessAnimation(false);

	SplitMeshDataByBone();
	
	
	if (upvec == FbxAxisSystem::EUpVector::eZAxis)
	{
		IWorldObj* pRotObj = new IWorldObj;
		pRotObj->m_pTransform->SetOrientation(-1.57, 0.0f, 0.0f);
		std::vector<SmartPointer<IWorldObj>> vecChildren;
		for (int i = 0; i < pRoot->GetChildCount(); ++i)
		{
			IWorldObj* pObj = pRoot->GetChild(i).get();
			vecChildren.push_back(pObj);
		}
		pRoot->removeAllChildren();
		pRoot->addChild(pRotObj);
		for each (SmartPointer<IWorldObj> pObj in vecChildren)
		{
			pRotObj->addChild(pObj);
		}
	}


	SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->CreateResource<PrefabResource>(m_exportResDir + m_strFbxAssetName + ".prefab.xml");
	pPrefab->m_pRoot = pRoot;
	pAsset->AddResource(m_exportResDir + m_strFbxAssetName + ".prefab.xml", pPrefab.get());
	pRoot->m_strName = getFileNameWithoutSuffix(path);

	if (pPrefab != nullptr)
	{
		PrefabAsset prefabAsset;
		prefabAsset.m_strPath = m_exportResDir + m_strFbxAssetName + ".prefab.xml";
		prefabAsset.AddResource(m_exportResDir + m_strFbxAssetName + ".prefab.xml", pPrefab.get());
		//AssetManager::GetInstance()->Save(&prefabAsset);

	}
	SkeletonResource* pSkeleRes = m_pAsset->GetResource<SkeletonResource>();
	if (pSkeleRes != nullptr)
	{
		PrefabAsset skelAasset;
		skelAasset.m_strPath = m_exportResDir + m_strFbxAssetName + ".skeleton.xml";
		skelAasset.AddResource(m_exportResDir + m_strFbxAssetName + ".skeleton.xml", pSkeleRes);
		//AssetManager::GetInstance()->Save(&skelAasset);

	}
	//
	return pAsset;
}
void ZG::FbxFileLoader::ProcessMesh(FbxNode* pNode)
{
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();
	SmartPointer<IWorldObj> pObj;
	if (pAttribute != nullptr)
	{
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::eMesh:
			{
				IWorldObj* pObj = m_mapFbxToObj[pNode];
				SmartPointer<MeshResource> pRes = ProcessMeshData(pNode, pObj);
			}
			break;
		}
	}
	int nChild = pNode->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		FbxNode* pChildNode = pNode->GetChild(i);
		ProcessMesh(pChildNode);
	}
}
SmartPointer<IWorldObj> FbxFileLoader::ProcessNode(FbxNode* pNode, SmartPointer<IWorldObj> pParent)
{
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();
	SmartPointer<IWorldObj> pObj;
	FbxSkeleton* pSkeleton = pNode->GetSkeleton();
	if (pAttribute == nullptr || pAttribute->GetAttributeType() != FbxNodeAttribute::EType::eSkeleton)
	{
		//
		pObj = new IWorldObj;
		SetWorldObjPropByFbxNode(pObj.get(), pNode);
		//m_mapFbxToObj[pNode] = pObj.get();
	}
	
	if (pAttribute != nullptr)
	{
		FbxNodeAttribute::EType type = pAttribute->GetAttributeType();
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::ePatch:
			{
				std::cout << "find patch!" << std::endl;
			}
			break;
			case FbxNodeAttribute::EType::eSkeleton:
			{
				if (pNode->GetSkeleton()->IsSkeletonRoot() == false)
				{
					break;
				}
				SkeletonObj* pSkel = new SkeletonObj;
				pObj = pSkel;
				SkeletonModule* pSklModule = m_mapFbxToObj[m_pRootFbxNode]->addModule<SkeletonModule>().get();
				pSklModule->m_strName = m_pRootFbxNode->GetName();
				//
				std::string skeletonPath = m_exportResDir;
				//skeletonPath = getFileDirectory(m_pAsset->m_strPath);
				if (m_SkeletonToFbxNode.size() == 0)
				{
					skeletonPath = skeletonPath + m_strFbxAssetName + ".skeleton.xml";
				}
				else
				{
					skeletonPath = skeletonPath + m_strFbxAssetName + numberToString(m_SkeletonToFbxNode.size(), 10) + ".skeleton.xml";
				}
				SkeletonResource* pSkeRes = ResourceManager<SkeletonResource>::GetInstance()->CreateResource<SkeletonResource>(skeletonPath).get();
				ProcessSkeleton(pNode, pSkeRes, pSkel);
				pSkeRes->UpdateMatrix();
				//
				pSklModule->SetSkeletonRes(pSkeRes);
				//
				m_pAsset->AddResource(skeletonPath, pSkeRes);
				return pSkel;
			}
			default:
			break;
		}
	}
	//
	int nChild = pNode->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		FbxNode* pChildNode = pNode->GetChild(i);
		SmartPointer<IWorldObj> pChild = ProcessNode(pChildNode, pObj);
		pObj->addChild(pChild);
		//m_mapFbxToObj[pChildNode] = pChild.get();
	}
	return pObj;
}
struct stNormalPolyIndex
{
	float x, y, z;//normal;
	int triIndex;
};
struct stSkinInfo
{
	int m_nIndex;
	float m_fWeight;
};
SmartPointer<MeshResource> FbxFileLoader::ProcessMeshData(FbxNode* pNode, SmartPointer<IWorldObj> obj)
{
	FbxMesh* pMesh = pNode->GetMesh();
	for each (FbxMesh* pM in vecDoneMeshList)
	{
		if (pM == pMesh)
		{
			return nullptr;
		}
	}
	vecDoneMeshList.push_back(pMesh);
	//
	std::string refPath = m_exportResDir + pNode->GetName() + ".mesh";
	//
	if (ResourceManager<MeshResource>::GetInstance()->GetResource(refPath) != nullptr)
	{
		refPath = m_exportResDir + pNode->GetName() + "_d" + ".mesh";
	}

	//vecMeshList.push_back(pMesh);
	SmartPointer<MeshResource> pMeshResource = ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>(refPath);
	m_pAsset->AddResource(refPath, pMeshResource.get());

	SmartPointer<IWorldObj> pModuleOwener;
	pModuleOwener = obj;


	if (pMesh == nullptr)
	{
		return nullptr;
	}
	//
	int triangleCount = pMesh->GetPolygonCount();
	int vertexCounter = 0;
	unsigned int cpCount = pMesh->GetControlPointsCount();
	std::vector<int> indexVec;
	std::vector<float> vertexVec;
	std::vector<float> areaVec;//ﾃ貊�
	std::vector<float> normalVec;
	std::vector<float> uvVec;
	std::vector<std::vector<stSkinInfo>> skinInfoVec;
	unsigned int nMaxBonePerVertex = 0;
	skinInfoVec.resize(cpCount);
	//get vertex pos
	for (unsigned int i = 0; i < cpCount; ++i)
	{
		float x, y, z;
		x = (float)pMesh->GetControlPointAt(i).mData[0];
		y = (float)pMesh->GetControlPointAt(i).mData[1];
		z = (float)pMesh->GetControlPointAt(i).mData[2];
		//std::cout << "vertexdata:" << x << " " << y << " " << z << std::endl;
		vertexVec.push_back(x);
		vertexVec.push_back(y);
		vertexVec.push_back(z);
	}
	//get index Buff
	for (int i = 0; i < triangleCount; ++i)
	{
		//for (int j = 0; j < 3; ++j)
		//{
		int ctrlPointIndex = pMesh->GetPolygonVertex(i, 0);
		indexVec.push_back(ctrlPointIndex);
		ctrlPointIndex = pMesh->GetPolygonVertex(i, 1);
		indexVec.push_back(ctrlPointIndex);
		ctrlPointIndex = pMesh->GetPolygonVertex(i, 2);
		indexVec.push_back(ctrlPointIndex);
		//}
	}
	//get triangle area
	for (int i = 0; i < triangleCount; ++i)
	{
		Vector3 v0, v1, v2;
		int index0, index1, index2;
		index0 = indexVec[i * 3 + 0];
		index1 = indexVec[i * 3 + 1];
		index2 = indexVec[i * 3 + 2];
		v0.m_fx = vertexVec[index0 * 3 + 0];
		v0.m_fy = vertexVec[index0 * 3 + 1];
		v0.m_fz = vertexVec[index0 * 3 + 2];
		//
		v1.m_fx = vertexVec[index1 * 3 + 0];
		v1.m_fy = vertexVec[index1 * 3 + 1];
		v1.m_fz = vertexVec[index1 * 3 + 2];
		//
		v2.m_fx = vertexVec[index2 * 3 + 0];
		v2.m_fy = vertexVec[index2 * 3 + 1];
		v2.m_fz = vertexVec[index2 * 3 + 2];
		//
		float L1, L2, L0;
		L1 = v0.distance(v1);
		L2 = v0.distance(v2);
		L0 = v1.distance(v2);
		float P = (L1 + L2 + L0) * 0.5f;
		float S = sqrt(P * (P - L2) * (P - L1) * (P - L0));
		areaVec.push_back(S);
	}
#pragma region GetNormal
	//get normal
	//FbxGeometryElementNormal
	FbxGeometryElementNormal* pNormal = pMesh->GetElementNormal(0);
	if (pNormal->GetMappingMode() == FbxLayerElement::eByControlPoint)
	{
		if (pNormal->GetReferenceMode() == FbxLayerElement::eDirect)
		{
			for (unsigned int i = 0; i < cpCount; ++i)
			{
				Vector3 normal;
				normal.m_fx = (float)pNormal->GetDirectArray().GetAt(i).mData[0];
				normal.m_fy = (float)pNormal->GetDirectArray().GetAt(i).mData[1];
				normal.m_fz = (float)pNormal->GetDirectArray().GetAt(i).mData[2];
				normalVec.push_back(normal.m_fx);
				normalVec.push_back(normal.m_fy);
				normalVec.push_back(normal.m_fz);

			}
		}
		else if (pNormal->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
		{

		}
	}
	else if (pNormal->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
	{
		//switch (pNormal->GetReferenceMode())
		//{
		if (pNormal->GetReferenceMode() == FbxLayerElement::eDirect)
		{
			std::map<int, std::vector<stNormalPolyIndex>> cpNormalIndexMap;
			//std::cout << "by Polygon ref direct!" << std::endl;
			for (int i = 0; i < triangleCount; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					int cpIndex = indexVec[i * 3 + j];
					stNormalPolyIndex np;
					np.triIndex = i;
					np.x = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[0];
					np.y = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[1];
					np.z = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[2];
					//std::cout << "Vertex Normal:" << np.x << " " << np.y << " " << np.z << std::endl;
					cpNormalIndexMap[cpIndex].push_back(np);
				}
			}
			for (unsigned int i = 0; i < cpCount; ++i)
			{
				float fAreaSum = 0;
				for_each(std::begin(cpNormalIndexMap[i]), std::end(cpNormalIndexMap[i]), [&](stNormalPolyIndex& npi)
				{
					fAreaSum += areaVec[npi.triIndex];
				}
				);
				//std::cout << "*********************************************** "<<std::endl;
				Vector3 vecNormal = Vector3::ZERO;
				for_each(std::begin(cpNormalIndexMap[i]), std::end(cpNormalIndexMap[i]), [&](stNormalPolyIndex& npi)
				{
					vecNormal = vecNormal + Vector3(npi.x, npi.y, npi.z) * (areaVec[npi.triIndex] / fAreaSum);
					//std::cout << npi.x << " " << npi.y << " " << npi.z << std::endl;
				}
				);
				vecNormal.normalize();
				normalVec.push_back(vecNormal.m_fx);
				normalVec.push_back(vecNormal.m_fy);
				normalVec.push_back(vecNormal.m_fz);
				//std::cout << "normal:" << vecNormal.m_fx << " " << vecNormal.m_fy << " " << vecNormal.m_fz << std::endl;
			}
		}
		//		break;
		else if (pNormal->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
		{

		}
	}
#pragma endregion
#pragma region GetUV
	FbxStringList lUVSetNameList;
	pMesh->GetUVSetNames(lUVSetNameList);

	//iterating over all uv sets
	for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
	{
		const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
		const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(lUVSetName);

		if (!lUVElement)
			continue;
	}
	int nLayerUV = pMesh->GetElementUVCount();
	//std::cout << "Texutre UV count:" << nLayerUV << std::endl;
	FbxGeometryElementUV* pLayerUV = pMesh->GetElementUV(0);
	if (pLayerUV == nullptr)
	{
		pLayerUV = pMesh->GetElementUV(1);
	}
	if (pLayerUV == nullptr)
	{
		std::cout << "texture uv0 cannot find" << std::endl;
	}
	else
	{
		if (pLayerUV->GetMappingMode() == FbxLayerElement::eByControlPoint)
		{
			if (pLayerUV->GetReferenceMode() == FbxLayerElement::eDirect)
			{
				uvVec.resize(cpCount * 2);
				for (unsigned int i = 0; i < cpCount; ++i)
				{
					float u, v;
					u = (float)pLayerUV->GetDirectArray().GetAt(i).mData[0];
					v = (float)pLayerUV->GetDirectArray().GetAt(i).mData[1];
					uvVec[i * 2 + 0] = u;
					uvVec[i * 2 + 1] = 1 - v;
				}
			}
			else if (pLayerUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
			{

			}
		}
		else if (pLayerUV->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
		{
			if (pLayerUV->GetReferenceMode() == FbxLayerElement::eDirect)
			{
				//std::cout << "texture uv by polygon direct" << std::endl;
			}
			else if (pLayerUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
			{
				//std::cout << "texture uv by polygon indirect" << std::endl;
				uvVec.resize(cpCount * 2);
				for (unsigned int i = 0; i < indexVec.size(); ++i)
				{
					//int index = pLayerUV->GetIndexArray().GetAt(i);
					int vIndex = i % 3;
					//if (vIndex == 2)
					//{
					//	vIndex = 1;
					//}
					//else if (vIndex == 1)
					//{
					//	vIndex = 2;
					//}
					int index = pMesh->GetTextureUVIndex(i / 3, vIndex);
					float u, v;
					u = (float)pLayerUV->GetDirectArray().GetAt(index).mData[0];
					v = (float)pLayerUV->GetDirectArray().GetAt(index).mData[1];
					uvVec[indexVec[i] * 2 + 0] = u;
					uvVec[indexVec[i] * 2 + 1] = 1 - v;
				}
				//for each (float c in uvVec)
				//{
				//	std::cout << "uv:" << c << std::endl;
				//}
			}
		}
	}


#pragma endregion
#pragma region AddSkinInfo
	bool bHasSkinInfo = false;
	int deformerCount = pMesh->GetDeformerCount();
	if (deformerCount >= 1)
	{
		bHasSkinInfo = true;
		FbxDeformer* pDeformer = pMesh->GetDeformer(0);
		int nDeformer = pMesh->GetDeformerCount();
		if (pDeformer != nullptr && pDeformer->GetDeformerType() == FbxDeformer::eSkin)
		{
			FbxSkin* pSkin = (FbxSkin*)(pDeformer);
			FbxCluster::ELinkMode linkMode = FbxCluster::eNormalize;
			FbxCluster* pCluster;
			FbxNode*	pLinkNode = nullptr;
			FbxMatrix	transformMatrix, transformLinkMatrix;
			int			clusterCount = pSkin->GetClusterCount();

			FbxNode* pSkeletonRoot = nullptr;
			SmartPointer<SkeletonResource> pSkeRes = nullptr;
			if (clusterCount >= 1)
			{
				pCluster = pSkin->GetCluster(0);
				pLinkNode = pCluster->GetLink();
				FbxSkeleton* pSkeleton = pLinkNode->GetSkeleton();
				pSkeRes = m_mapSkeleton[pSkeleton];
			}
			for (int i = 0; i < clusterCount; ++i)
			{
				pCluster = pSkin->GetCluster(i);
				//FbxAMatrix pMat, pMatLink;
				//pCluster->GetTransformMatrix(pMat);
				//pCluster->GetTransformLinkMatrix(pMatLink);
				pLinkNode = pCluster->GetLink();
				int nCtrlPoint = pCluster->GetControlPointIndicesCount();
				int* pCtrlPointIndices = pCluster->GetControlPointIndices();
				double* pCtrlPointWeights = pCluster->GetControlPointWeights();
				int ctrlPointIndex;
				int boneIndex;
				boneIndex = pSkeRes->m_pRoot->GetBoneIndexByName(pLinkNode->GetName());
				for (int j = 0; j < nCtrlPoint; ++j)
				{
					ctrlPointIndex = pCtrlPointIndices[j];
					stSkinInfo skinInfo;
					skinInfo.m_nIndex = boneIndex;
					skinInfo.m_fWeight = (float)pCtrlPointWeights[j];
					skinInfoVec[ctrlPointIndex].push_back(skinInfo);
				}

			}
		}
	}
	for each (std::vector<stSkinInfo> vecSkin in skinInfoVec)
	{
		if (vecSkin.size() > nMaxBonePerVertex)
		{
			nMaxBonePerVertex = vecSkin.size();
		}
	}
#pragma  endregion
#pragma region CalTangent
#pragma endregion
#pragma region AddMeshResource
	SmartPointer<Mesh> pMeshModule;
	pMeshModule = pModuleOwener->addModule<Mesh>();
	pMeshModule->SetMeshResource(pMeshResource);
	EnumIndexDesc eIndexDesc = EIndexInt;
	int nIndexLength = indexVec.size();
	if (cpCount <= 65535)
	{
		eIndexDesc = EIndexShort;
	}
	void* pTemp = nullptr;
	if (eIndexDesc == EIndexInt)
	{
		pTemp = new unsigned short[nIndexLength * 2];
		//int nOffset = 0;
		int* pBuff = (int*)pTemp;
		for each (int var in indexVec)
		{
			*pBuff = var;
			pBuff++;
		}
	}
	else if (eIndexDesc == EIndexShort)
	{
		pTemp = new unsigned short[nIndexLength];
		//int nOffset = 0;
		unsigned short* pBuff = (unsigned short*)pTemp;
		for each (int var in indexVec)
		{
			*pBuff = var;
			pBuff++;
		}
	}
	pMeshResource->m_IndexData->indexNum = indexVec.size();
	pMeshResource->m_IndexData->indexDesc = eIndexDesc;
	pMeshResource->m_IndexData->pData = pTemp;
	//vertex data
	int nVBOffset = 0;
	VertexData::VertexDataDesc desc;
	//
	desc.usedesc = EVertexPosition;
	desc.typedesc = EVertexTypeFloat3;
	desc.nOffset = 0;
	pMeshResource->m_VertexData->vecDataDesc.push_back(desc);
	nVBOffset = sizeof(float) * 3;
	//
	desc.usedesc = EVertexNormal;
	desc.typedesc = EVertexTypeFloat3;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData->vecDataDesc.push_back(desc);
	nVBOffset += sizeof(float) * 3;
	//
	if (uvVec.size() != 0)
	{
		desc.usedesc = EVertexUV;
		desc.typedesc = EVertexTypeFloat2;
		desc.nOffset = nVBOffset;
		pMeshResource->m_VertexData->vecDataDesc.push_back(desc);
		nVBOffset += sizeof(float) * 2;
	}

	if (bHasSkinInfo)
	{
		//blend index
		desc.usedesc = EVertexBlendIndex;
		desc.typedesc = EVertexTypeUByte4;
		desc.nOffset = nVBOffset;
		pMeshResource->m_VertexData->vecDataDesc.push_back(desc);
		nVBOffset += sizeof(unsigned char) * 4;
		//blend weight
		desc.usedesc = EVertexBlendWeight;
		desc.typedesc = EVertexTypeFloat4;
		desc.nOffset = nVBOffset;
		pMeshResource->m_VertexData->vecDataDesc.push_back(desc);
		nVBOffset += sizeof(float) * 4;
		pMeshResource->m_VertexData->m_BonePerVert = nMaxBonePerVertex;
	}
	else
	{
		pMeshResource->m_VertexData->m_BonePerVert = 0;
	}



	pMeshResource->m_VertexData->m_nNumVertex = cpCount;
	pMeshResource->m_VertexData->pData = new unsigned char[nVBOffset * cpCount];
	for (unsigned int cpIndex = 0; cpIndex < cpCount; ++cpIndex)
	{
		for (unsigned int i = 0; i < pMeshResource->m_VertexData->vecDataDesc.size(); ++i)
		{
			VertexData::VertexDataDesc desc = pMeshResource->m_VertexData->vecDataDesc[i];
			void* pTempVoid = (unsigned char*)pMeshResource->m_VertexData->pData + desc.nOffset + cpIndex * pMeshResource->m_VertexData->GetVertexDataLength();
			switch (desc.typedesc)
			{

				case EVertexTypeFloat4:
				{
					float* pFloat = (float*)pTempVoid;
					switch (pMeshResource->m_VertexData->vecDataDesc[i].usedesc)
					{
						case EVertexBlendWeight:
						{
							std::vector<float> vecBlendWeight;
							for (unsigned int ii = 0; ii < 4; ++ii)
							{
								vecBlendWeight.push_back(0.0f);
							}
							for (unsigned int j = 0; j < skinInfoVec[cpIndex].size(); ++j)
							{
								vecBlendWeight[j] = skinInfoVec[cpIndex][j].m_fWeight;
							}
							for (unsigned int ii = 0; ii < 4; ++ii)
							{
								*pFloat = vecBlendWeight[ii];
								pFloat++;
							}
						}
						default:
						break;
					}

				}
				break;
				case EVertexTypeUByte4:
				{
					unsigned char* pChar = (unsigned char*)pTempVoid;
					switch (pMeshResource->m_VertexData->vecDataDesc[i].usedesc)
					{
						case EVertexBlendIndex:
						{
							std::vector<unsigned char> vecBlendIndex;
							for (int ii = 0; ii < 4; ++ii)
							{
								vecBlendIndex.push_back(0);
							}
							for (unsigned int j = 0; j < skinInfoVec[cpIndex].size(); ++j)
							{
								vecBlendIndex[j] = skinInfoVec[cpIndex][j].m_nIndex;
							}
							for (int ii = 0; ii < 4; ++ii)
							{
								*pChar = vecBlendIndex[ii];
								pChar++;
							}
						}
						default:
						break;
					}
				}
				case EVertexTypeFloat3:
				{
					float* pFloat = (float*)pTempVoid;
					//for (int j = 0; j < cpCount; ++j)
					//{
					if (pMeshResource->m_VertexData->vecDataDesc[i].usedesc == EVertexPosition)
					{
						*pFloat = vertexVec[cpIndex * 3 + 0];
						//std::cout <<"VertexBin:"<< *pFloat<<" ";
						pFloat++;
						*pFloat = vertexVec[cpIndex * 3 + 1];
						//std::cout << *pFloat<<" ";
						pFloat++;
						*pFloat = vertexVec[cpIndex * 3 + 2];
						//std::cout << *pFloat << std::endl;
						pFloat++;
					}
					else if (pMeshResource->m_VertexData->vecDataDesc[i].usedesc == EVertexNormal)
					{
						*pFloat = normalVec[cpIndex * 3 + 0];
						//std::cout << "NormalBin:" << *pFloat << " ";
						pFloat++;
						*pFloat = normalVec[cpIndex * 3 + 1];
						//std::cout << *pFloat << " ";
						pFloat++;
						*pFloat = normalVec[cpIndex * 3 + 2];
						//std::cout << *pFloat << std::endl;
						pFloat++;
					}
					//}
				}
				break;
				case EVertexTypeFloat2:
				{
					float* pFloat = (float*)pTempVoid;
					//for (int j = 0; j < cpCount; ++j)
					//{
					switch (pMeshResource->m_VertexData->vecDataDesc[i].usedesc)
					{
						case EVertexUV:
						{
							*pFloat = uvVec[cpIndex * 2 + 0];
							//std::cout << "UV:" << *pFloat << " ";
							pFloat++;
							*pFloat = uvVec[cpIndex * 2 + 1];
							//std::cout << *pFloat << " "<<std::endl;
							pFloat++;
						}
						break;
						default:
						break;
					}
					//}
				}
				break;
				case EVertexTypeFloat1:
				{

				}
				break;
				default:
				break;
			}
		}
	}

#pragma endregion
	//
	pMeshResource->m_VertexData->ComputeTangent(*pMeshResource->m_IndexData.get());
	//
#pragma region processmaterial
	//material
	int nMatCount = pNode->GetMaterialCount();
	//std::cout << pNode->GetName() << " has material count:" << nMatCount << std::endl;
	FbxLayerElementArrayTemplate<int> *tArray = new FbxLayerElementArrayTemplate<int>(EFbxType::eFbxInt);
	pMesh->GetMaterialIndices(&tArray);
	if (tArray == nullptr)
	{
		return pMeshResource;
	}
	int nMatIndex = tArray->GetAt(0);
	FbxSurfaceMaterial* pMat = pNode->GetMaterial(nMatIndex);
	if (pMat == nullptr)
	{
		std::cout << "can not find material for " << pNode->GetName() << std::endl;
	}
	//
	SmartPointer<RasterMaterial> pMatRes = ProcessMaterial(pMat, bHasSkinInfo);
	m_pAsset->AddResource(pMatRes->GetRefPath(), pMatRes.get());
	pMeshModule->m_pSharedMaterial = pMatRes.get();
	//
#pragma endregion
	//return pMeshResource;
#pragma region split mesh
	//return nullptr;
	bool bRemoveMainMesh = false;
	int nMaterialCount = pNode->GetMaterialCount();
	if (nMaterialCount <= 1)
	{
		return nullptr;
	}
	FbxLayerElementArrayTemplate<int> *tmpArray = new FbxLayerElementArrayTemplate<int>(EFbxType::eFbxInt);
	pMesh->GetMaterialIndices(&tmpArray);
	//std::cout << "triangle count:" << pMesh->GetPolygonCount() << std::endl;
	//std::cout << "vertex count:" << pMesh->GetControlPointsCount() << std::endl;
	//std::cout << "array count:" << tmpArray->GetCount() << std::endl;
	for (int i = 0; i < pNode->GetMaterialCount(); ++i)
	{
		FbxSurfaceMaterial* pMat = pNode->GetMaterial(i);
		std::vector<int> subIndexVec;
		std::vector<int> subPolyVec;
		std::vector<int> subVertVec;
		std::map<int, int> mapIndex;//<pMeshResrouce,pSubMesh>
		std::unordered_map<int, int> remapIndex;//<pSubMesh,pMeshResource>
		for (int j = 0; j < tmpArray->GetCount(); ++j)
		{
			if (tmpArray->GetAt(j) == i)
			{
				subPolyVec.push_back(j);
			}
		}
		for each (int polyIndex in subPolyVec)
		{
			subIndexVec.push_back(indexVec[polyIndex * 3 + 0]);
			subIndexVec.push_back(indexVec[polyIndex * 3 + 1]);
			subIndexVec.push_back(indexVec[polyIndex * 3 + 2]);
		}
		int nIndexCount = 0;
		for each (int index in subIndexVec)
		{
			if (mapIndex.find(index) == std::end(mapIndex))
			{
				mapIndex[index] = nIndexCount;
				remapIndex[nIndexCount] = index;
				nIndexCount++;
			}
		}
		for_each(std::begin(subIndexVec), std::end(subIndexVec), [&](int& i)
		{
			i = mapIndex[i];
		});
		if (subIndexVec.size() == 0)
		{
			continue;;
		}
		std::string meshName = getFileNameWithoutSuffix(refPath);
		std::string subRefPath = m_exportResDir + meshName + "_" + pMat->GetName() + ".mesh";
		SmartPointer<MeshResource> pSubMesh = ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>(subRefPath);// (new MeshResource);
		m_pAsset->AddResource(subRefPath, pSubMesh.get());
		SmartPointer<Mesh> pSubMeshModule = obj->addModule<Mesh>();
		pSubMeshModule->SetMeshResource(pSubMesh);
		bRemoveMainMesh = true;
		//
		SmartPointer<RasterMaterial> pMatRes = ProcessMaterial(pMat, bHasSkinInfo);
		m_pAsset->AddResource(pMatRes->GetRefPath(), pMatRes.get());
		pSubMeshModule->m_pSharedMaterial = pMatRes.get();
		//



		pSubMesh->m_VertexData->vecDataDesc = pMeshResource->m_VertexData->vecDataDesc;
		pSubMesh->m_VertexData->m_nNumVertex = mapIndex.size();
		pSubMesh->m_VertexData->m_BonePerVert = nMaxBonePerVertex;
		//check skin info
		/*if (pMeshResource->m_VertexData->m_BonePerVert > 0)
		{
		int skindescindex = 0;
		for each (VertexData::VertexDataDesc desc in pSubMesh->m_VertexData->vecDataDesc)
		{
		if (desc.usedesc == EVertexBlendIndex)
		{
		break;
		}
		skindescindex++;
		}
		bool bRemoveSkin = false;
		for (unsigned int i = 0; i < pSubMesh->m_VertexData->m_nNumVertex; ++i)
		{
		void* pSrc = pMeshResource->m_VertexData->GetElementData(skindescindex, remapIndex[i]);
		unsigned char* pUByte = (unsigned char*)pSrc;
		if (*pUByte == 0 && *(pUByte + 1) == 0 && *(pUByte + 2) == 0 && *(pUByte + 3) == 0)
		{
		bRemoveSkin = true;
		}
		}
		if (bRemoveSkin == true)
		{
		std::vector<VertexData::VertexDataDesc>::iterator iter = pSubMesh->m_VertexData->vecDataDesc.begin();
		for (; iter != pSubMesh->m_VertexData->vecDataDesc.end();)
		{
		if (iter->usedesc == EVertexBlendIndex || iter->usedesc == EVertexBlendWeight)
		{
		iter = pSubMesh->m_VertexData->vecDataDesc.erase(iter);
		continue;
		}
		iter++;
		}
		}
		}*/

		//vertex data
		int nVertexDataLength = pSubMesh->m_VertexData->GetVertexDataLength();
		int nBuffLength = nVertexDataLength * pSubMesh->m_VertexData->m_nNumVertex;
		if (nBuffLength <= 0)
		{
			break;
		}
		void* pVertexBuff = new unsigned char[nBuffLength];
		pSubMesh->m_VertexData->pData = pVertexBuff;
		int descIndex = 0;
		for each (VertexData::VertexDataDesc desc in pSubMesh->m_VertexData->vecDataDesc)
		{
			int nElementLength = pSubMesh->m_VertexData->GetTypeLength(desc);

			for (unsigned int i = 0; i < pSubMesh->m_VertexData->m_nNumVertex; ++i)
			{
				void* pDst;
				void* pSrc;
				pDst = pSubMesh->m_VertexData->GetElementData(descIndex, i);
				pSrc = pMeshResource->m_VertexData->GetElementData(descIndex, remapIndex[i]);
				memcpy(pDst, pSrc, nElementLength);
			}
			descIndex++;
		}
		//index data
		pSubMesh->m_IndexData->indexNum = subIndexVec.size();
		pSubMesh->m_IndexData->indexDesc = pMeshResource->m_IndexData->indexDesc;
		if (pSubMesh->m_IndexData->indexDesc == EIndexShort)
		{
			pSubMesh->m_IndexData->pData = (void*)new unsigned char[subIndexVec.size() * sizeof(short)];
			short* pShortData = (short*)pSubMesh->m_IndexData->pData;
			for each (int index in subIndexVec)
			{
				*pShortData = index;
				pShortData++;
			}
		}
		else if (pSubMesh->m_IndexData->indexDesc == EIndexInt)
		{
			pSubMesh->m_IndexData->pData = (void*)new unsigned char[subIndexVec.size() * sizeof(int)];
			short* pIntData = (short*)pSubMesh->m_IndexData->pData;
			for each (int index in subIndexVec)
			{
				*pIntData = index;
				pIntData++;
			}
		}
		int nPropertyCount = pMat->GetSrcPropertyCount();
		FbxProperty kProp = pMat->GetFirstProperty();
	}
	if (bRemoveMainMesh == true)
	{
		pModuleOwener->removeModule(pMeshModule.get());
		ResourceManager<MeshResource>::GetInstance()->RemoveResource(refPath);
		m_pAsset->RemoveResource(refPath);
	}
#pragma endregion
	return pMeshResource;
}

SmartPointer<IWorldObj> FbxFileLoader::ProcessSkeleton(FbxNode* pNode, SkeletonResource* pRes, SkeletonObj* pObj)
{
	
	//
	FbxSkeleton* pSke = pNode->GetSkeleton();
	Bone* pRoot = new Bone();
	pRes->m_pRoot = pRoot;
	int BoneIndex = 0;
	ProcessBone(pRes, pRoot, pNode, BoneIndex, pObj,pNode);
	m_mapSkeleton[pSke] = pRes;
	m_mapSkeObj[pSke] = pObj;
	m_SkeResToSkeRoot[pRes] = pObj;
	pRes->m_nBoneNum = pRes->m_mapBone.size();
	return nullptr;

}

void FbxFileLoader::ProcessBone(SmartPointer<SkeletonResource> pRes, Bone* pBone, FbxNode* pFbxObj, int& index, SkeletonObj* pSkeObj, FbxNode* pRoot)
{
	FbxEuler::EOrder order = pFbxObj->RotationOrder.Get();
	//m_mapFbxToObj[pFbxObj] = pSkeObj;
	if (pBone == nullptr)
	{
		return;
	}
	FbxCluster* pCluster = m_NodeToCluster[pFbxObj];
	FbxVector4 fs, fr, ft;
	FbxAMatrix lLinkMatrix, lMatrix, lGeometryMatrix, inverseBindPos, lCurWorld;
	if (pCluster == nullptr)
	{
		pCluster = FbxCluster::Create(dynamic_cast<FbxAsset*>(m_pAsset)->m_pFbxScene, "");
		pCluster->SetLink(pFbxObj);
		pCluster->SetLinkMode(FbxCluster::eNormalize);
		pCluster->SetTransformLinkMatrix(pFbxObj->EvaluateGlobalTransform());
		
		//FbxAMatrix rootMatrix = vecSkinMeshList[0]->GetNode()->EvaluateGlobalTransform().Inverse();
		FbxAMatrix rootMatrix;
		for each (std::pair<FbxNode*,FbxCluster*> p in m_NodeToCluster)
		{
			if (p.second != nullptr)
			{
				p.second->GetTransformMatrix(rootMatrix);
				break;
			}
		}
		pCluster->SetTransformMatrix(rootMatrix);
	}
	else
	{
		int c = 0;
	}
	if (pCluster != nullptr)
	{

		pCluster->GetTransformMatrix(lMatrix);
		pCluster->GetTransformLinkMatrix(lLinkMatrix);
		pFbxObj->GetTransform();
		FbxNode* pAssociateNode = pCluster->GetAssociateModel();
		if (pAssociateNode != nullptr)
		{
			const FbxVector4 lT = pAssociateNode->GetGeometricTranslation(FbxNode::eSourcePivot);
			const FbxVector4 lR = pAssociateNode->GetGeometricRotation(FbxNode::eSourcePivot);
			const FbxVector4 lS = pAssociateNode->GetGeometricScaling(FbxNode::eSourcePivot);

			lGeometryMatrix = FbxAMatrix(lT, lR, lS);
		}
		inverseBindPos = lLinkMatrix.Inverse() * lMatrix * lGeometryMatrix;
		//inverseBindPos = lLinkMatrix.Inverse();
		ft = inverseBindPos.GetT();
		fr = inverseBindPos.GetR();
		fs = inverseBindPos.GetS();
	}
	else
	{

		/*FbxSkeleton* pSkeleton = pFbxObj->GetSkeleton();*/
	}

	//
	m_SkeletonToFbxNode[pRes.get()].push_back(pFbxObj);
	FbxSkeleton* pSkeleton = pFbxObj->GetSkeleton();
	m_mapSkeleton[pSkeleton] = pRes;
	if (pSkeleton == nullptr)
	{
		return;
	}
	//FbxPropertyT<FbxDouble3> t = pFbxObj->LclTranslation;
	//FbxPropertyT<FbxDouble3> r = pFbxObj->LclRotation;
	//FbxPropertyT<FbxDouble3> s = pFbxObj->LclScaling;
	Vector3 vs, vr, vt;
	//
	vt.m_fx = (float)ft.mData[0];
	vt.m_fy = (float)ft.mData[1];
	vt.m_fz = (float)ft.mData[2];

	vr.m_fx = AngleToRad((float)fr.mData[0]);
	vr.m_fy = AngleToRad((float)fr.mData[1]);
	vr.m_fz = AngleToRad((float)fr.mData[2]);


	vs.m_fx = (float)fs.mData[0];
	vs.m_fy = (float)fs.mData[1];
	vs.m_fz = (float)fs.mData[2];

	pBone->m_matInversePos = Matrix44::FromVector(vt, vr, vs);
	//
	//
	SetWorldObjPropByFbxNode(pSkeObj, pFbxObj);
	//pSkeObj->m_strName = pFbxObj->GetName();
	if (pCluster != nullptr)
	{

	}

	//pSkeObj->m_pTransform->SetWorldTransform();
	char temp[10];
	_itoa_s(index, temp, 10);
	pBone->m_strName = pFbxObj->GetName();
	//pObj->SetName(pBone->m_strName.c_str());
	pBone->nIndex = index;
	//std::cout << "boneindex:" << index<<std::endl;
	pRes->m_mapBone[index] = pBone;
	//index++;
	int nChildCount = pFbxObj->GetChildCount();
	for (int i = 0; i < nChildCount; ++i)
	{
		FbxNode* pChild = pFbxObj->GetChild(i);
		FbxSkeleton* pChildSke = pChild->GetSkeleton();
		if (nullptr == pChildSke)
		{
			FbxSkeleton* lSkeletonRootAttribute = FbxSkeleton::Create(dynamic_cast<FbxAsset*>(m_pAsset)->m_pFbxScene, pChild->GetName());
			lSkeletonRootAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
			pChild->SetNodeAttribute(lSkeletonRootAttribute);
			pChildSke = lSkeletonRootAttribute;
			//SmartPointer<IWorldObj> pChildObj = ProcessNode(pChild, pSkeObj);
			//pSkeObj->addChild(pChildObj);
			//continue;
		}
		index++;
		Bone* pChildBone = new Bone;
		pBone->vecChild.push_back(pChildBone);
		SkeletonObj *pChildObj = new SkeletonObj;
		pSkeObj->addChild(pChildObj);
		ProcessBone(pRes, pChildBone, pChild, index, pChildObj,pRoot);
	}

}

FbxNode* FbxFileLoader::GetSkeletonRoot(FbxNode* pNode)
{
	FbxSkeleton* pSke = pNode->GetSkeleton();
	if (pSke == nullptr)
	{
		return nullptr;
	}
	//if (pSke->GetSkeletonType() == FbxSkeleton::eRoot)
	//{
	//	return pNode;
	//}
	FbxNode* pParent = pNode->GetParent();
	if (pParent->GetSkeleton() == nullptr)
	{
		return pNode;
	}
	FbxNode* pParentSke = GetSkeletonRoot(pParent);
	if (pParent != nullptr)
	{
		return pParentSke;
	}
	return nullptr;
}

SmartPointer<RasterMaterial> FbxFileLoader::ProcessMaterial(FbxSurfaceMaterial* pMat, bool bHasSkinInfo)
{
	if (m_mapMaterial.find(pMat) != std::end(m_mapMaterial))
	{
		return m_mapMaterial[pMat].SmartPointerCast<RasterMaterial>();
	}
	FbxSurfacePhong* pSrfPhong = (FbxSurfacePhong*)pMat;
	int nProp = pMat->GetSrcPropertyCount();
	FbxProperty pProp = pSrfPhong->GetFirstProperty();


	SmartPointer<RasterMaterial> pMatRes = ResourceManager<MaterialResource>::GetInstance()->CreateResource<RasterMaterial>(m_exportResDir + pMat->GetName() + ".smat.xml");
	m_mapMaterial[pMat] = pMatRes.get();

	if (_access(m_exportResDir.c_str(), 0) == -1)
	{
		_mkdir(m_exportResDir.c_str());
	}
	while (pProp.IsValid())
	{
		//std::cout << pProp.GetName() << std::endl;
		pProp = pMat->GetNextProperty(pProp);
		int nTextureCount = pProp.GetSrcObjectCount<FbxFileTexture>();
		for (int i = 0; i < nTextureCount; ++i)
		{
			FbxFileTexture* pTex = pProp.GetSrcObject<FbxFileTexture>(i);
			//std::cout << "find tex:" << pTex->GetName() << std::endl;
			std::cout << pProp.GetName() << ":" << getFileName(pTex->GetName()).c_str() << std::endl;

			std::string strProperty = pProp.GetName();
			std::string fileName = getFileName(pTex->GetName());

			if (_tcsstr(strProperty.c_str(), "Diffuse") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);


				std::string texPath = m_exportResDir + fileName;
				if (_access((m_exportResDir + fileName).c_str(), 0) == -1)
				{ 
					CpyFile(pTex->GetName(), m_exportResDir + fileName);
				}
				if (_access((strTexturePath + fileName).c_str(), 0) != -1)
				{
					texPath = strTexturePath + fileName;
				}
				std::string fbxPath = m_pAsset->m_strPath;
				fbxPath = getFileDirectory(fbxPath);
				if (_access((fbxPath + fileName).c_str(), 0) != -1)
				{
					texPath = fbxPath + "/" + pTex->GetName();
				}
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(texPath).get();

			}
			else if (_tcsstr(strProperty.c_str(), "Specular") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				
				std::string texPath = m_exportResDir + fileName;
				if (_access((m_exportResDir + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), m_exportResDir + fileName);
				}
				if (_access((strTexturePath + fileName).c_str(), 0) != -1)
				{
					texPath = strTexturePath + fileName;
				}
				std::string fbxPath = m_pAsset->m_strPath;
				fbxPath = getFileDirectory(fbxPath);
				if (_access((fbxPath + fileName).c_str(), 0) != -1)
				{
					texPath = fbxPath + "/" + pTex->GetName();
				}
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(texPath).get();
			}
			else if (_tcsstr(strProperty.c_str(), "Normal") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				std::string texPath = m_exportResDir + fileName;
				if (_access((m_exportResDir + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), m_exportResDir + fileName);
				}
				if (_access((strTexturePath + fileName).c_str(), 0) != -1)
				{
					texPath = strTexturePath + fileName;
				}
				std::string fbxPath = m_pAsset->m_strPath;
				fbxPath = getFileDirectory(fbxPath);
				if (_access((fbxPath + fileName).c_str(), 0) != -1)
				{
					texPath = fbxPath + "/" + pTex->GetName();
				}
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(texPath).get();
			}
			else if (_tcsstr(strProperty.c_str(), "Emissive") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				std::string texPath = m_exportResDir + fileName;
				if (_access((m_exportResDir + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), m_exportResDir + fileName);
				}
				if (_access((m_exportResDir + fileName).c_str(), 0) != -1)
				{
					texPath = m_exportResDir + fileName;
				}
				std::string fbxPath = m_pAsset->m_strPath;
				fbxPath = getFileDirectory(fbxPath);
				if (_access((fbxPath + fileName).c_str(), 0) != -1)
				{
					texPath = fbxPath + "/" + pTex->GetName();
				}
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(texPath).get();
			}
		}
		MaterialPass* pPass = new MaterialPass();
		TMatArg<GameColor>* pArg = new TMatArg<GameColor>(EMATARGTYPECOLOR);
		pArg->m_Data = GameColor::white;
		//pMatRes->AddArg("MainColor", pArg);
		pMatRes->AddPass("First", pPass);
		AssetManager::GetInstance()->LoadAsset("./data/shader/VertexStandard.vsm");
		AssetManager::GetInstance()->LoadAsset("./data/shader/VertexSkin.vsm");
		AssetManager::GetInstance()->LoadAsset("./data/shader/FragSpec.fsm");
		pPass->m_eVertexShaderType = EVERTEXSHADERORIGIN;
		pPass->m_eFragShaderType = EFRAGSHADERORIGIN;
		if (bHasSkinInfo == true)
		{
			pPass->m_pVertexShader = ResourceManager<VertexShader>::GetInstance()->GetResource("./data/shader/VertexSkin.vsm");
		}
		else
		{
			pPass->m_pVertexShader = ResourceManager<VertexShader>::GetInstance()->GetResource("./data/shader/VertexStandard.vsm");
		}

		pPass->m_pFragShader = ResourceManager<FragShader>::GetInstance()->GetResource("./data/shader/FragSpec.fsm");
		//
		//XMLElement* pPass = doc.NewElement("RenderPass");
		//root->InsertEndChild(pPass);
		//XMLElement* pVertShader = doc.NewElement("VertexShader");
		//XMLElement* pFragShader = doc.NewElement("FragElem");
		//pPass->SetAttribute("Name", "bladesouldefault");
		//pPass->SetAttribute("BRDF", "BlinPhong");
		//pPass->InsertEndChild(pVertShader);
		//pPass->InsertEndChild(pFragShader);
		//pVertShader->SetAttribute("refPath", "./data/shader/VertexStandard.vsm");
		//pVertShader->SetAttribute("ShaderType", "Origin");
		//pFragShader->SetAttribute("refPath", "./data/shader/FragSpec.fsm");
		//pVertShader->SetAttribute("ShaderType", "Origin");
		//pFragShader->SetAttribute("ShaderType", "Origin");
		//
	}
	return pMatRes;

}

void ZG::FbxFileLoader::ProcessSkeletonRoot(SkeletonModule* pModule,IWorldObj* pMeshObj)
{
	//std::vector<SmartPointer<Mesh>> vecRemove;
	//{
	//	std::vector<SmartPointer<Mesh>> vecMesh;
	//	pMeshObj->GetAllModule<Mesh>(vecMesh);

	//	int nMesh = vecMesh.size();
	//	for (int j = 0; j < nMesh; ++j)
	//	{
	//		Mesh* pMesh = pModule->m_pOwnerObj->addModule<Mesh>().get();
	//		pMesh->CopyFrom(vecMesh[j].get());
	//		pModule->AddMesh(pMesh);

	//		vecMesh[j]->m_pOwnerObj->removeModule(vecMesh[j].get());
	//	}
	//	//
	//	//vecRemove.push_back(pChild);
	//}
	//for each (IWorldObj* pWorldObj in vecRemove)
	//{
	//	//pObj->removeChild(pWorldObj);
	//}
}

void ZG::FbxFileLoader::ProcessAnimation(bool bPerFrame /*= false*/)
{
	FbxAsset* pAsset = dynamic_cast<FbxAsset*>(m_pAsset);
	std::string path = pAsset->m_strPath;
	//
	int nCount = pAsset->m_pFbxScene->GetSrcObjectCount<FbxAnimStack>();
	FbxAnimStack* pAniStack = pAsset->m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	if (pAniStack != nullptr)
	{
		//return pAsset;
		//std::cout << "find Stack:"<<pAniStack->GetName() << std::endl;

	}
	else
	{
		return;
	}
	int nAnimLayerCount = pAniStack->GetMemberCount<FbxAnimLayer>();
	for (int i = 0; i < nAnimLayerCount; ++i)
	{
		FbxAnimLayer* pLayer = pAniStack->GetMember<FbxAnimLayer>(i);
		//std::cout << "find layer:" << i << " " << pLayer->GetName() << std::endl;

		for each (std::pair<SkeletonResource*, std::vector<FbxNode*>> p in m_SkeletonToFbxNode)
		{
			//

			std::string aniName = pAniStack->GetName();
			if (m_SkeletonToFbxNode.size() > 1)
			{
				char temp[10];
				_itoa_s(i, temp, 10, 10);
				aniName = aniName + temp;
			}
			std::string refPath = m_exportResDir + aniName + ".animation.xml";
			AnimationResource* pAniRes = ResourceManager<AnimationResource>::GetInstance()->CreateResource<AnimationResource>(refPath).get();
			pAniRes->m_bIsSkinAnimation = true;
			pAniRes->m_eAniMode = EANILOOP;
			AnimationTrack* pTrack = new AnimationTrack(pAniRes);
			//
			SkeletonModule* pModule = m_mapFbxToObj[m_pRootFbxNode]->GetModule<SkeletonModule>();
			pModule->AddAnimationTrack(pTrack);
			if (pModule->GetDefaultAnimationTrack() == nullptr)
			{
				pModule->SetDefaultAnimationTrack(pTrack);
			}
			//
			for each (FbxNode* pNode in p.second)
			{
				int nTransCount = 0;
				int nScaleCount = 0;
				int nRotCount = 0;
				int nMaxKeyCount = 0;
				FbxAnimCurve* pAniCurveTX = pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X);
				if (pAniCurveTX != nullptr)
				{
					nMaxKeyCount = pAniCurveTX->KeyGetCount();
					nTransCount = nMaxKeyCount;
				}
				FbxAnimCurve* pAniCurveTY = pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				FbxAnimCurve* pAniCurveTZ = pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				//
				FbxAnimCurve* pAniCurveRX = pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X);
				if (pAniCurveRX != nullptr)
				{
					nRotCount = pAniCurveRX->KeyGetCount();
					if (nRotCount > nMaxKeyCount)
					{
						nMaxKeyCount = nRotCount;
					}
				}
				FbxAnimCurve* pAniCurveRY = pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				FbxAnimCurve* pAniCurveRZ = pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				FbxAnimCurve* pAniCurveSX = pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X);
				if (pAniCurveSX != nullptr)
				{
					nScaleCount = pAniCurveSX->KeyGetCount();
					if (nScaleCount > nMaxKeyCount)
					{
						nMaxKeyCount = nScaleCount;
					}
				}
				FbxAnimCurve* pAniCurveSY = pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				FbxAnimCurve* pAniCurveSZ = pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				if (pAniCurveTX == nullptr && pAniCurveRX == nullptr && pAniCurveSX == nullptr)
				{
					continue;
				}

				AnimationCurve<stTransformData>* pTransCurve = new AnimationCurve<stTransformData>(EANITRANSFORM);
				std::cout << "add curve:" << pNode->GetName() << std::endl;
				//
				Vector3 vecLastTrans(pNode->LclTranslation.Get().mData[0], pNode->LclTranslation.Get().mData[1], pNode->LclTranslation.Get().mData[2]);
				Vector3 vecLastRot(AngleToRad(pNode->LclRotation.Get().mData[0]), AngleToRad(pNode->LclRotation.Get().mData[1]), AngleToRad(pNode->LclRotation.Get().mData[2]));
				Vector3 vecLastScale(pNode->LclScaling.Get().mData[0], pNode->LclScaling.Get().mData[1], pNode->LclScaling.Get().mData[2]);
				pAniRes->m_fLegnth = 0.0f;
				for (int i = 0; i < nMaxKeyCount; ++i)
				{
					KeyFrame<stTransformData> kf;
					float fTime = 0.0f;
					if (pAniCurveTX != nullptr && i < nTransCount)
					{
						FbxAnimCurveKey key;
						key = pAniCurveTX->KeyGet(i);
						float fValueTX = key.GetValue();
						fTime = key.GetTime().GetSecondDouble();
						kf.m_fTime = fTime;
						kf.m_KeyFrameData.m_vecTranslate.m_fx = fValueTX;
						kf.m_KeyFrameData.m_vecTranslate.m_fy = pAniCurveTY->KeyGet(i).GetValue();
						kf.m_KeyFrameData.m_vecTranslate.m_fz = pAniCurveTZ->KeyGet(i).GetValue();
						vecLastTrans = kf.m_KeyFrameData.m_vecTranslate;
					}
					else
					{
						kf.m_KeyFrameData.m_vecTranslate = vecLastTrans;
					}

					if (pAniCurveRX != nullptr && i < nRotCount)
					{
						kf.m_KeyFrameData.m_vecRotation.m_fx = AngleToRad(pAniCurveRX->KeyGet(i).GetValue());
						kf.m_KeyFrameData.m_vecRotation.m_fy = AngleToRad(pAniCurveRY->KeyGet(i).GetValue());
						kf.m_KeyFrameData.m_vecRotation.m_fz = AngleToRad(pAniCurveRZ->KeyGet(i).GetValue());
						vecLastRot = kf.m_KeyFrameData.m_vecRotation;
						fTime = pAniCurveRX->KeyGet(i).GetTime().GetSecondDouble();
					}
					else
					{
						kf.m_KeyFrameData.m_vecRotation = vecLastRot;
					}

					if (pAniCurveSX != nullptr && i < nScaleCount)
					{
						kf.m_KeyFrameData.m_vecScale.m_fx = pAniCurveSX->KeyGet(i).GetValue();
						kf.m_KeyFrameData.m_vecScale.m_fy = pAniCurveSY->KeyGet(i).GetValue();
						kf.m_KeyFrameData.m_vecScale.m_fz = pAniCurveSZ->KeyGet(i).GetValue();
						vecLastScale = kf.m_KeyFrameData.m_vecScale;
						fTime = pAniCurveSX->KeyGet(i).GetTime().GetSecondDouble();
					}
					else
					{
						kf.m_KeyFrameData.m_vecScale = vecLastScale;
					}
					pTransCurve->AddKeyFrame(fTime, kf.m_KeyFrameData);
					if (pAniRes->m_fLegnth < fTime)
					{
						pAniRes->m_fLegnth = fTime;
					}

				}
				pAniRes->m_mapCurves[pNode->GetName()] = pTransCurve;

			}
			//
			m_pAsset->AddResource(refPath, pAniRes);


			if (m_Options.m_bExportAnimation == true)
			{
				AnimationAsset AniAsset;
				AniAsset.AddResource(refPath, pAniRes);
				AnimationAssetLoader loader;
				loader.Save(&AniAsset);
			}
		}
	}
}



void ZG::FbxFileLoader::SetWorldObjPropByFbxNode(IWorldObj* pObj, FbxNode* pFbxObj)
{
	m_mapFbxToObj[pFbxObj] = pObj;
	pObj->m_strName = pFbxObj->GetName();
	FbxTransform nodeTrans = pFbxObj->GetTransform();
	FbxDouble3 trans = pFbxObj->LclTranslation.Get();
	FbxDouble3 rot = pFbxObj->LclRotation.Get();
	FbxDouble3 scal = pFbxObj->LclScaling.Get();

	FbxDouble3 gTrans = pFbxObj->GeometricTranslation.Get();
	FbxDouble3 gRot = pFbxObj->GeometricRotation.Get();
	FbxDouble3 gScale = pFbxObj->GeometricScaling.Get();

	FbxAMatrix g, l;
	g.SetTRS(gTrans, gRot, gScale);
	l.SetTRS(trans, rot, scal);

	FbxAMatrix total;
	total = l * g;

	FbxVector4 t, r, s;
	t = total.GetT();
	r = total.GetR();
	s = total.GetS();
	//
	SmartPointer<Transform> pTransform = pObj->GetModule(0).SmartPointerCast<Transform>();
	pTransform->SetTranslate((float)t.mData[0], (float)t.mData[1], (float)t.mData[2]);
	pTransform->SetScale((float)s.mData[0], (float)s.mData[1], (float)s.mData[1]);
	pTransform->SetOrientation(AngleToRad((float)r.mData[0]), AngleToRad((float)r.mData[1]), AngleToRad((float)r.mData[2]));
}

void ZG::FbxFileLoader::PostProcessSkinMesh(IWorldObj* pNode)
{
	
	SkeletonModule* pModule = pNode->GetModule<SkeletonModule>();
	if (pModule != nullptr)
	{
		SkeletonObj* pObj = m_SkeResToSkeRoot[pModule->GetSkeletonRes()];
		for each (FbxMesh* pMesh in vecMeshList)
		{
			if (IsSkeletonMesh(pModule->GetSkeletonRes(), pMesh))
			{
				FbxNode* pNode = pMesh->GetNode();
				IWorldObj* pObjMesh = m_mapFbxToObj[pNode];
				ProcessSkeletonRoot(pModule, pObjMesh);
			}
		}
	}
	int nChild = pNode->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		IWorldObj* pChild = pNode->GetChild(i).get();
		PostProcessSkinMesh(pChild);
	}
}

void ZG::FbxFileLoader::SplitMeshDataByBone()
{
	std::vector<MeshResource*> vecMesh;
	m_pAsset->GetAllResource<MeshResource>(vecMesh);
	for each (MeshResource* pMesh in vecMesh)
	{
		MeshVertexData* pVertexData = pMesh->m_VertexData.get();
		if (pVertexData->m_BonePerVert == 0)
		{
			continue;
		}
		IndexData*		pIndexData = pMesh->m_IndexData.get();
		std::map<int, bool> mapBoneIndex;
		for (int i = 0; i < pVertexData->m_nNumVertex; ++i)
		{
			unsigned char* pIndex = (unsigned char*)pVertexData->GetElementDataByDesc(EVertexBlendIndex, i);
			if (pIndex == nullptr)
			{
				continue;
			}
			for (int i = 0; i < 4; ++i)
			{
				mapBoneIndex[*(pIndex + i)] = true;
			}
		}
		unsigned int nBoneNumber = mapBoneIndex.size();
		std::vector<int> vecBoneIndex;
		for each (std::pair<int, bool> p in mapBoneIndex)
		{
			vecBoneIndex.push_back(p.first);
		}
		//
		std::cout << pMesh->GetRefPath().c_str() << " has bone:" << nBoneNumber << std::endl;

		std::unordered_map<int, int> indexRemapOldToNew;
		for (int i = 0; i < nBoneNumber; ++i)
		{
			indexRemapOldToNew[vecBoneIndex[i]] = i;
		}
		//
		if (nBoneNumber >= MAX_BONE_NUMBER)
		{
			//pMesh->
		}
		//
#pragma region Remap
		pMesh->m_VertexData->m_nBoneNumber = nBoneNumber;
		for (int i = 0; i < pVertexData->m_nNumVertex; ++i)
		{
			unsigned char* pIndex = (unsigned char*)pVertexData->GetElementDataByDesc(EVertexBlendIndex, i);
			if (pIndex == nullptr)
			{
				continue;
			}
			for (int i = 0; i < 4; ++i)
			{
				*(pIndex + i) = indexRemapOldToNew[*(pIndex + i)];
			}
		}
		SkinSubMeshInfo* subSkinMeshInfo = new SkinSubMeshInfo;
		subSkinMeshInfo->m_vecBoneIndex = vecBoneIndex;
		subSkinMeshInfo->m_nStartIndex = 0;
		subSkinMeshInfo->m_nPrimitiveCount = pIndexData->indexNum / 3;
		pVertexData->m_vecSubSkinInfo.push_back(subSkinMeshInfo);
#pragma  endregion
		//
		//unsigned int nSplitMeshSize = (nBoneNumber + 63) / 64;
	}

}

void ZG::FbxFileLoader::InitSkeletonCluster()
{
	//FbxNode* pParent = pSkeletonRoot->GetParent();
	//int nChild = pParent->GetChildCount();
	//for (int i = 0; i < nChild; ++i)
	//{
	//	FbxNode* pChild = pParent->GetChild(i);
	//	if (pChild != nullptr)
	//	{
	//		if (pChild->GetMesh() != nullptr)
	//		{
	//			FbxSkin *pSkinDeformer = (FbxSkin*)pChild->GetMesh()->GetDeformer(0, FbxDeformer::eSkin);
	//			int nCluster = pSkinDeformer->GetClusterCount();
	//			for (int i = 0; i < nCluster; ++i)
	//			{
	//				FbxCluster* pCluster = pSkinDeformer->GetCluster(i);
	//				m_NodeToCluster[pCluster->GetLink()] = pCluster;
	//			}
	//		}
	//	}
	//}
	for (int i = 0; i < vecMeshList.size(); ++i)
	{
		FbxSkin *pSkinDeformer = (FbxSkin*)vecMeshList[i]->GetDeformer(0, FbxDeformer::eSkin);
		if (pSkinDeformer != nullptr)
		{
			int nCluster = pSkinDeformer->GetClusterCount();
			for (int i = 0; i < nCluster; ++i)
			{
				FbxCluster* pCluster = pSkinDeformer->GetCluster(i);
				m_NodeToCluster[pCluster->GetLink()] = pCluster;
			}
		}
	}
}

void ZG::FbxFileLoader::PreGetMesh(FbxNode* pNode)
{
	if (pNode->GetMesh() != nullptr)
	{
		vecMeshList.push_back(pNode->GetMesh());
		FbxDeformer* pDeformer = pNode->GetMesh()->GetDeformer(0);
		
		int nDefaormerCount = pNode->GetMesh()->GetDeformerCount();
		if (pDeformer != nullptr && pDeformer->GetDeformerType() == FbxDeformer::eSkin)
		{
			FbxSkin* pSkin = (FbxSkin*)pDeformer;
			int nClusterCount = pSkin->GetClusterCount();
			vecSkinMeshList.push_back(pNode->GetMesh());
		}
	}
	int nChild = pNode->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		FbxNode* pChild = pNode->GetChild(i);
		PreGetMesh(pChild);
	}
}

FbxNode* ZG::FbxFileLoader::GetWorldNodeByFbxNode(IWorldObj* pObj)
{
	for each (std::pair<FbxNode*, IWorldObj*> p in m_mapFbxToObj)
	{
		if (p.second == pObj)
		{
			return p.first;
		}
	}
	return nullptr;
}

bool ZG::FbxFileLoader::IsSkeletonMesh(SkeletonResource* pResource, FbxMesh* pMesh)
{
	return true;
}
