#include "stdafx.h"
#include "FbxFileLoader.h"
#include "FbxAsset.h"
#include "FbxAppManager.h"
#include "ResourceMananger.h"
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
IAsset* FbxFileLoader::Load(string path, void* pArg /*= nullptr*/)
{
	m_fileDir = getFileDirectory(path);
	string name = getFileName(path);
	name = removeSuffix(name);
	FbxAsset* pAsset = new FbxAsset;
	m_pAsset = pAsset;
	pAsset->m_strPath = path;
	pAsset->m_pFbxScene = FbxScene::Create(FbxAppManager::GetInstance()->m_pFbxSdkManager, path.c_str());
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
	pAsset->m_pFbxScene->Clear();
	bImportStatus = pImporter->Import(pAsset->m_pFbxScene);
	pImporter->Destroy();



	//FbxGeometryConverter kConverter(FbxAppManager::GetInstance()->m_pFbxSdkManager);
	//if (kConverter.SplitMeshesPerMaterial(pAsset->m_pFbxScene, false))
	//{
	//	std::cout << "Error:can not split per material!" << std::endl;
	//}
	////FbxCriteria kfbxCriteria;
	////kfbxCriteria.ObjectType()
	//std::vector<FbxMesh*> meshVec;
	//for (int i = 0; i < pAsset->m_pFbxScene->GetSrcObjectCount(FbxCriteria::ObjectType(FbxMesh::ClassId)); ++i)
	//{
	//	FbxMesh* pMesh = (FbxMesh*)pAsset->m_pFbxScene->GetSrcObject(FbxCriteria::ObjectType(FbxMesh::ClassId), i);
	//	meshVec.push_back(pMesh);
	//	//FbxGeometryConverter kConverter(FbxAppManager::GetInstance()->m_pFbxSdkManager);
	//	//if (kConverter.SplitMeshPerMaterial(pMesh, true))
	//	//{
	//	//	std::cout << "Error:can not split per material!" << std::endl;
	//	//}
	//	//if (!pMesh->GetDeformerCount())
	//	//	std::cout << "Error: mesh " << i << " with no deformers." << std::endl;
	//	//else
	//	//	std::cout << "Mesh " << i << " with " << pMesh->GetDeformerCount() << " deformers." << std::endl;
	//}
	//for each (FbxMesh* pMesh in meshVec)
	//{
	//	FbxGeometryConverter kConverter(FbxAppManager::GetInstance()->m_pFbxSdkManager);
	//	if (kConverter.SplitMeshPerMaterial(pMesh, false))
	//	{
	//		std::cout << pMesh->GetName()<< "Error:can not split per material!" << std::endl;
	//	}
	//}
	FbxNode* pRootNode = pAsset->m_pFbxScene->GetRootNode();
	if (pRootNode == nullptr)
	{
		return pAsset;
	}
	IWorldObj* pRoot = ProcessNode(pRootNode, path,nullptr,nullptr);


	shared_ptr<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->CreateResource<PrefabResource>(m_fileDir + name + ".prefab.xml");
	pPrefab->m_pRoot = pRoot;
	pAsset->AddResource(m_fileDir + name + ".prefab.xml", pPrefab);
	//
	return pAsset;
}

IWorldObj* FbxFileLoader::ProcessNode(FbxNode* pNode, string refPath, IWorldObj* pParent, IWorldObj* pSkeletonObj)
{
	refPath = refPath + "/" + pNode->GetName() + ".mesh";
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();
	IWorldObj* pObj = new IWorldObj;
	pObj->m_strName = pNode->GetName();
	FbxTransform nodeTrans = pNode->GetTransform();
	FbxDouble3 trans = pNode->LclTranslation.Get();
	FbxDouble3 rot = pNode->LclRotation.Get();
	FbxDouble3 scal = pNode->LclScaling.Get();
	Transform* pTransform = (Transform*)pObj->GetModule(0);
	pTransform->SetTranslate((float)trans.mData[0], (float)trans.mData[2], (float)trans.mData[1]);
	pTransform->SetScale((float)scal.mData[0], (float)scal.mData[2], (float)scal.mData[1]);
	pTransform->SetOrientation((float)rot.mData[0], (float)rot.mData[2], (float)rot.mData[1]);

	//IWorldObj* pSkeltonRoot = nullptr;
	if (pAttribute != nullptr)
	{
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::eMesh:
			{

				shared_ptr<MeshResource> pRes = ProcessMesh(pNode, refPath,pObj,pSkeletonObj);

			}
			break;
			case FbxNodeAttribute::EType::eSkeleton:
			{
				FbxSkeleton* pskl = pNode->GetSkeleton();
				FbxNode* pSkeRootNode = GetSkeletonRoot(pNode);
				FbxSkeleton* pSklRoot = pSkeRootNode->GetSkeleton();
				if (pSkeRootNode == pNode)
				{
					pSkeletonObj = pObj;
				}
				if (m_mapSkeleton.find(pSklRoot) == std::end(m_mapSkeleton))
				{
					ProcessSkeleton(pSkeRootNode, m_fileDir + pNode->GetName() + ".skeleton.xml", pObj);
				}
			}
			default:
			break;
		}
	}
	int nChild = pNode->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		FbxNode* pChildNode = pNode->GetChild(i);
		IWorldObj* pChild = ProcessNode(pChildNode, refPath, nullptr, pSkeletonObj);
		pObj->addChild(pChild);
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
shared_ptr<MeshResource> FbxFileLoader::ProcessMesh(FbxNode* pNode, string refPath, IWorldObj* obj,IWorldObj* pSkeletonObj)
{
	FbxMesh* pMesh = pNode->GetMesh();
	for each (FbxMesh* pM in vecMeshList)
	{
		if (pM == pMesh)
		{
			return nullptr;
		}
	}
	//
	char temp[25];
	_itoa_s((int)pMesh, temp, 10);
	refPath = m_fileDir + pNode->GetName() + ".mesh";
	//
	if (ResourceManager<MeshResource>::GetInstance()->GetResource(refPath) != nullptr)
	{
		refPath = m_fileDir + pNode->GetName() + "a" + ".mesh";
	}

	vecMeshList.push_back(pMesh);
	shared_ptr<MeshResource> pMeshResource = ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>(refPath);
	m_pAsset->AddResource(refPath, pMeshResource);



	IWorldObj* pModuleOwener = obj;
	//


	if (pMesh == nullptr)
	{
		return nullptr;
	}
	//
	int triangleCount = pMesh->GetPolygonCount();
	int vertexCounter = 0;
	int cpCount = pMesh->GetControlPointsCount();
	std::vector<int> indexVec;
	std::vector<float> vertexVec;
	std::vector<float> areaVec;//Ãæ»ý
	std::vector<float> normalVec;
	std::vector<float> uvVec;
	std::vector<vector<stSkinInfo>> skinInfoVec;
	unsigned int nMaxBonePerVertex = 0;
	skinInfoVec.resize(cpCount);
	//get vertex pos
	for (int i = 0; i < cpCount; ++i)
	{
		float x, y, z;
		x = (float)pMesh->GetControlPointAt(i).mData[0];
		y = (float)pMesh->GetControlPointAt(i).mData[2];
		z = (float)pMesh->GetControlPointAt(i).mData[1];
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
		ctrlPointIndex = pMesh->GetPolygonVertex(i, 2);
		indexVec.push_back(ctrlPointIndex);
		ctrlPointIndex = pMesh->GetPolygonVertex(i, 1);
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
					np.y = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[2];
					np.z = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[1];
					//std::cout << "Vertex Normal:" << np.x << " " << np.y << " " << np.z << std::endl;
					cpNormalIndexMap[cpIndex].push_back(np);
				}
			}
			for (int i = 0; i < cpCount; ++i)
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
		std::cout << "texture uv0 cannot find" << std::endl;
	}
	if (pLayerUV->GetMappingMode() == FbxLayerElement::eByControlPoint)
	{
		if (pLayerUV->GetReferenceMode() == FbxLayerElement::eDirect)
		{

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
				if (vIndex == 2)
				{
					vIndex = 1;
				}
				else if (vIndex == 1)
				{
					vIndex = 2;
				}
				int index = pMesh->GetTextureUVIndex(i / 3, vIndex);
				float u, v;
				u = (float)pLayerUV->GetDirectArray().GetAt(index).mData[0];
				v = (float)pLayerUV->GetDirectArray().GetAt(index).mData[1];
				uvVec[indexVec[i] * 2 + 0] = u;
				uvVec[indexVec[i] * 2 + 1] = 1-v;
			}
			//for each (float c in uvVec)
			//{
			//	std::cout << "uv:" << c << std::endl;
			//}
		}
	}

#pragma endregion
#pragma region AddSkinInfo
	int deformerCount = pMesh->GetDeformerCount();
	if (deformerCount == 1)
	{
		FbxDeformer* pDeformer = pMesh->GetDeformer(0);
		if (pDeformer != nullptr && pDeformer->GetDeformerType() == FbxDeformer::eSkin)
		{
			FbxSkin* pSkin = (FbxSkin*)(pDeformer);
			FbxCluster::ELinkMode linkMode = FbxCluster::eNormalize;
			FbxCluster* pCluster;
			FbxNode*	pLinkNode;
			FbxMatrix	transformMatrix, transformLinkMatrix;
			int			clusterCount = pSkin->GetClusterCount();

			FbxNode* pSkeletonRoot = nullptr;
			shared_ptr<SkeletonResource> pSkeRes = nullptr;
			if (clusterCount >= 1)
			{
				pCluster = pSkin->GetCluster(0);
				pLinkNode = pCluster->GetLink();
				pSkeletonRoot = GetSkeletonRoot(pLinkNode);
				FbxSkeleton* pSR = pSkeletonRoot->GetSkeleton();


				if (m_mapSkeleton.find(pSR) == std::end(m_mapSkeleton))
				{
					ProcessSkeleton(pSkeletonRoot, m_fileDir + pSkeletonRoot->GetName() + ".skeleton.xml");
					
				}

				pModuleOwener = m_mapSkeObj[pSR];
				pSkeRes = m_mapSkeleton[pSR];

					
				
			}
			for (int i = 0; i < clusterCount; ++i)
			{
				pCluster = pSkin->GetCluster(i);
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
#pragma region AddMeshResource
	Mesh* pMeshModule;
	pMeshModule = pModuleOwener->addModule<Mesh>();
	pMeshModule->SetMeshResource(pMeshResource);
	IndexData::EnumIndexDesc eIndexDesc = IndexData::EIndexInt;
	int nIndexLength = indexVec.size();
	if (nIndexLength <= 65535)
	{
		eIndexDesc = IndexData::EIndexShort;
	}
	void* pTemp = nullptr;
	if (eIndexDesc == IndexData::EIndexInt)
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
	else if (eIndexDesc == IndexData::EIndexShort)
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
	pMeshResource->m_IndexData.indexNum = indexVec.size();
	pMeshResource->m_IndexData.indexDesc = eIndexDesc;
	pMeshResource->m_IndexData.pData = pTemp;
	//vertex data
	int nVBOffset = 0;
	VertexData::VertexDataDesc desc;
	//
	desc.usedesc = VertexData::EVertexPosition;
	desc.typedesc = VertexData::EVertexTypeFloat3;
	desc.nOffset = 0;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset = cpCount * sizeof(float) * 3;
	//
	desc.usedesc = VertexData::EVertexNormal;
	desc.typedesc = VertexData::EVertexTypeFloat3;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(float) * 3;
	//
	desc.usedesc = VertexData::EVertexUV;
	desc.typedesc = VertexData::EVertexTypeFloat2;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(float) * 2;
	//blend index
	desc.usedesc = VertexData::EVertexBlendIndex;
	desc.typedesc = VertexData::EVertexTypeByte4;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(unsigned char) * 4;
	//blend weight
	desc.usedesc = VertexData::EVertexBlendWeight;
	desc.typedesc = VertexData::EVertexTypeFloat4;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(float) * 4;

	pMeshResource->m_VertexData.nBoneNum = nMaxBonePerVertex;
	pMeshResource->m_VertexData.nNumVertex = cpCount;
	pMeshResource->m_VertexData.pData = new unsigned char[nVBOffset];
	for (unsigned int i = 0; i < pMeshResource->m_VertexData.vecDataDesc.size(); ++i)
	{
		VertexData::VertexDataDesc desc = pMeshResource->m_VertexData.vecDataDesc[i];
		void* pTempVoid = (unsigned char*)pMeshResource->m_VertexData.pData + desc.nOffset;
		switch (desc.typedesc)
		{
			
			case VertexData::EVertexTypeFloat4:
			{
				float* pFloat = (float*)pTempVoid;
				switch (pMeshResource->m_VertexData.vecDataDesc[i].usedesc)
				{
					case VertexData::EVertexBlendWeight:
					{
						std::vector<float> vecBlendWeight;
						for (unsigned int ii = 0; ii < 4; ++ii)
						{
							vecBlendWeight.push_back(0.0f);
						}
						for (unsigned int j = 0; j < skinInfoVec[i].size(); ++j)
						{
							vecBlendWeight[j] = skinInfoVec[i][j].m_fWeight;
						}
						for (unsigned int ii = 0; ii < 4; ++ii)
						{
							*pFloat = vecBlendWeight[ii];
						}
					}
					default:
					break;
				}

			}
			break;
			case VertexData::EVertexTypeByte4:
			{
				unsigned char* pChar = (unsigned char*)pTempVoid;
				switch (pMeshResource->m_VertexData.vecDataDesc[i].usedesc)
				{
					case VertexData::EVertexBlendIndex:
					{
						std::vector<unsigned char> vecBlendIndex;
						for (int ii = 0; ii < 4; ++ii)
						{
							vecBlendIndex.push_back(0);
						}
						for (unsigned int j = 0; j < skinInfoVec[i].size(); ++j)
						{
							vecBlendIndex[j] = skinInfoVec[i][j].m_nIndex;
						}
						for (int ii = 0; ii < 4; ++ii)
						{
							*pChar = vecBlendIndex[i];
						}
					}
					default:
					break;
				}
			}
			case VertexData::EVertexTypeFloat3:
			{
				float* pFloat = (float*)pTempVoid;
				for (int j = 0; j < cpCount; ++j)
				{
					if (pMeshResource->m_VertexData.vecDataDesc[i].usedesc == VertexData::EVertexPosition)
					{
						*pFloat = vertexVec[j * 3 + 0];
						//std::cout <<"VertexBin:"<< *pFloat<<" ";
						pFloat++;
						*pFloat = vertexVec[j * 3 + 1];
						//std::cout << *pFloat<<" ";
						pFloat++;
						*pFloat = vertexVec[j * 3 + 2];
						//std::cout << *pFloat << std::endl;
						pFloat++;
					}
					else if (pMeshResource->m_VertexData.vecDataDesc[i].usedesc == VertexData::EVertexNormal)
					{
						*pFloat = normalVec[j * 3 + 0];
						//std::cout << "NormalBin:" << *pFloat << " ";
						pFloat++;
						*pFloat = normalVec[j * 3 + 1];
						//std::cout << *pFloat << " ";
						pFloat++;
						*pFloat = normalVec[j * 3 + 2];
						//std::cout << *pFloat << std::endl;
						pFloat++;
					}
				}
			}
			break;
			case VertexData::EVertexTypeFloat2:
			{
				float* pFloat = (float*)pTempVoid;
				for (int j = 0; j < cpCount; ++j)
				{
					switch (pMeshResource->m_VertexData.vecDataDesc[i].usedesc)
					{
						case VertexData::EVertexUV:
						{
							*pFloat = uvVec[j * 2 + 0];
							//std::cout << "UV:" << *pFloat << " ";
							pFloat++;
							*pFloat = uvVec[j * 2 + 1];
							//std::cout << *pFloat << " "<<std::endl;
							pFloat++;
						}
						break;
						default:
						break;
					}
				}
			}
			break;
			case VertexData::EVertexTypeFloat1:
			{

			}
			break;
			default:
			break;
		}

	}
#pragma endregion
#pragma region processmaterial
	//material
	int nMatCount = pNode->GetMaterialCount();
	//std::cout << pNode->GetName() << " has material count:" << nMatCount << std::endl;
	FbxLayerElementArrayTemplate<int> *tArray = new FbxLayerElementArrayTemplate<int>(EFbxType::eFbxInt);
	pMesh->GetMaterialIndices(&tArray);
	int nMatIndex = tArray->GetAt(0);
	FbxSurfaceMaterial* pMat = pNode->GetMaterial(nMatIndex);
	if (pMat == nullptr)
	{
		std::cout << "can not find material for " << pNode->GetName() << std::endl;
	}
	//
	shared_ptr<RasterMaterial> pMatRes = ProcessMaterial(pMat);
	m_pAsset->AddResource(pMatRes->GetRefPath(), pMatRes);
	pMeshModule->m_pMaterial = pMatRes;
	//
#pragma endregion
	return pMeshResource;
#pragma region split mesh
	return nullptr;
	int nMaterialCount = pNode->GetMaterialCount();
	if (nMaterialCount <= 1)
	{
		return nullptr;
	}
	FbxLayerElementArrayTemplate<int> *tmpArray = new FbxLayerElementArrayTemplate<int>(EFbxType::eFbxInt);
	pMesh->GetMaterialIndices(&tmpArray);
	std::cout << "triangle count:" << pMesh->GetPolygonCount() << std::endl;
	std::cout << "vertex count:" << pMesh->GetControlPointsCount() << std::endl;
	std::cout << "array count:" << tmpArray->GetCount() << std::endl;
	//for (int i = 0; i < tmpArray->GetCount(); ++i)
	//{
	//	std::cout << tmpArray->GetAt(i) << " ";
	//}
	//std::cout << std::endl;
	for (int i = 0; i < pNode->GetMaterialCount(); ++i)
	{
		FbxSurfaceMaterial* pMat = pNode->GetMaterial(i);
		std::vector<int> subIndexVec;
		std::vector<int> subPolyVec;
		std::vector<int> subVertVec;
		//std::vector<int> subIndexVertVec;
		std::map<int, int> m_mapIndex;//<pMeshResrouce,pSubMesh>
		std::unordered_map<int, int> m_remapIndex;//<pSubMesh,pMeshResource>
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
			if (m_mapIndex.find(index) == std::end(m_mapIndex))
			{
				m_mapIndex[index] = nIndexCount;
				m_remapIndex[nIndexCount] = index;
				nIndexCount++;
			}
		}
		for_each(std::begin(subIndexVec), std::end(subIndexVec), [&](int& i)
		{
			i = m_mapIndex[i];
		});
		if (subIndexVec.size() == 0)
		{
			break;
		}
		string subRefPath = refPath + pMat->GetName();
		shared_ptr<MeshResource> pSubMesh = ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>(refPath);// (new MeshResource);
		//ResourceMananger<MeshResource>::GetInstance()->AddResource(subRefPath, pSubMesh);
		m_pAsset->AddResource(subRefPath, pSubMesh);
		//pSubMesh->m_refPath = refPath;
		pSubMesh->m_VertexData.vecDataDesc = pMeshResource->m_VertexData.vecDataDesc;
		pSubMesh->m_VertexData.nNumVertex = m_mapIndex.size();
		int nVertexDataLength = pSubMesh->m_VertexData.GetVertexDataLength();
		int nBuffLength = nVertexDataLength * m_mapIndex.size();
		if (nBuffLength <= 0)
		{
			break;
		}
		void* pVertexBuff = new unsigned char[nBuffLength];
		pSubMesh->m_VertexData.pData = pVertexBuff;
		//vertex data
		for (unsigned int i = 0; i < pSubMesh->m_VertexData.vecDataDesc.size(); ++i)
		{
			pSubMesh->m_VertexData.vecDataDesc[i].nOffset = pMeshResource->m_VertexData.vecDataDesc[i].nOffset * pSubMesh->m_VertexData.nNumVertex / pMeshResource->m_VertexData.nNumVertex;
		}
		int descIndex = 0;
		for each (VertexData::VertexDataDesc desc in pSubMesh->m_VertexData.vecDataDesc)
		{
			int nElementLength = pSubMesh->m_VertexData.GetTypeLength(desc);

			for (unsigned int i = 0; i < pSubMesh->m_VertexData.nNumVertex; ++i)
			{
				void* pDst;
				void* pSrc;
				pDst = pSubMesh->m_VertexData.GetElementData(descIndex, i);
				pSrc = pMeshResource->m_VertexData.GetElementData(descIndex, m_remapIndex[i]);
				memcpy(pDst, pSrc, nElementLength);
			}
			descIndex++;
		}
		//index data
		pSubMesh->m_IndexData.indexNum = subIndexVec.size();
		pSubMesh->m_IndexData.indexDesc = pMeshResource->m_IndexData.indexDesc;
		if (pSubMesh->m_IndexData.indexDesc == IndexData::EIndexShort)
		{
			pSubMesh->m_IndexData.pData = (void*)new unsigned char[subIndexVec.size() * sizeof(short)];
			short* pShortData = (short*)pSubMesh->m_IndexData.pData;
			for each (int index in subIndexVec)
			{
				*pShortData = index;
				pShortData++;
			}
		}
		else if (pSubMesh->m_IndexData.indexDesc == IndexData::EIndexInt)
		{
			pSubMesh->m_IndexData.pData = (void*)new unsigned char[subIndexVec.size() * sizeof(int)];
			short* pIntData = (short*)pSubMesh->m_IndexData.pData;
			for each (int index in subIndexVec)
			{
				*pIntData = index;
				pIntData++;
			}
		}


		//	FbxSurfaceMaterial* pMat = pNode->GetMaterial(i);
		int nPropertyCount = pMat->GetSrcPropertyCount();
		FbxProperty kProp = pMat->GetFirstProperty();
		while (kProp.IsValid() == true)
		{
			int nSrcObjCount = kProp.GetSrcObjectCount();
			for (int j = 0; j < nSrcObjCount; ++j)
			{

				FbxFileTexture* pObj = kProp.GetSrcObject<FbxFileTexture>(j);
				if (pObj != nullptr)
				{
					std::cout << "Material:" << kProp.GetName() << std::endl;
					std::cout << "Material:" << pObj->GetName() << std::endl;
					std::cout << "Material:" << pObj->GetMediaName() << std::endl;
					//std::cout << "Material:" << pObj->GetRelativeFileName() << std::endl;
				}
			}
			kProp = pMat->GetNextProperty(kProp);
		}
		//std::cout << "add mesh:" << subRefPath.c_str() << std::endl;
	}
#pragma endregion
}

IWorldObj* FbxFileLoader::ProcessSkeleton(FbxNode* pNode, string refPath, IWorldObj* pObj /*= nullptr*/)
{
	FbxSkeleton* pSke = pNode->GetSkeleton();
	if (m_mapSkeleton.find(pSke) != std::end(m_mapSkeleton))
	{
		return nullptr;
	}
	refPath = m_fileDir + pNode->GetName() + ".skeleton.xml";
	shared_ptr<SkeletonResource> pSkeleton = ResourceManager<SkeletonResource>::GetInstance()->CreateResource<SkeletonResource>(refPath);
	Bone* pRoot = new Bone();
	pSkeleton->m_pRoot = pRoot;
	ProcessBone(pSkeleton, pRoot, pNode, 0);
	m_pAsset->AddResource(refPath, pSkeleton);
	m_mapSkeleton[pSke] = pSkeleton;
	m_mapSkeObj[pSke] = pObj;
	pSkeleton->m_nBoneNum = pSkeleton->m_mapBone.size();
	return nullptr;
	
}

void FbxFileLoader::ProcessBone(shared_ptr<SkeletonResource> pRes, Bone* pBone, FbxNode* pObj, int index)
{
	if (pBone == nullptr)
	{
		return;
	}
	FbxSkeleton* pSkeleton = pObj->GetSkeleton();
	if (pSkeleton == nullptr)
	{
		return;
	}
	FbxPropertyT<FbxDouble3> t = pObj->LclTranslation;
	FbxPropertyT<FbxDouble3> r = pObj->LclRotation;
	FbxPropertyT<FbxDouble3> s = pObj->LclScaling;
	pBone->t.m_fx = (float)t.Get().mData[0];
	pBone->t.m_fy = (float)t.Get().mData[1];
	pBone->t.m_fz = (float)t.Get().mData[2];

	pBone->r.m_fx = (float)r.Get().mData[0];
	pBone->r.m_fy = (float)r.Get().mData[1];
	pBone->r.m_fz = (float)r.Get().mData[2];


	pBone->s.m_fx = (float)s.Get().mData[0];
	pBone->s.m_fy = (float)s.Get().mData[1];
	pBone->s.m_fz = (float)s.Get().mData[2];

	char temp[10];
	_itoa_s(index, temp, 10);	
	pBone->m_strName = string("Bone") + temp;
	pObj->SetName(pBone->m_strName.c_str());
	pBone->nIndex = index;
	pRes->m_mapBone[index] = pBone;
	//index++;
	int nChildCount = pObj->GetChildCount();
	for (int i = 0; i < nChildCount; ++i)
	{
		FbxNode* pChild = pObj->GetChild(i);
		FbxSkeleton* pChildSke = pChild->GetSkeleton();
		if (nullptr == pChildSke)
		{
			continue;
		}
		index++;
		Bone* pChildBone = new Bone;
		pBone->vecChild.push_back(pChildBone);
		ProcessBone(pRes, pChildBone, pChild, index);
	}

}

FbxNode* FbxFileLoader::GetSkeletonRoot(FbxNode* pNode)
{
	FbxSkeleton* pSke = pNode->GetSkeleton();
	if (pSke == nullptr)
	{
		return nullptr;
	}
	if (pSke->GetSkeletonType() == FbxSkeleton::eRoot)
	{
		return pNode;
	}
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

shared_ptr<RasterMaterial> FbxFileLoader::ProcessMaterial(FbxSurfaceMaterial* pMat)
{
	if (m_mapMaterial.find(pMat) != std::end(m_mapMaterial))
	{
		return dynamic_pointer_cast<RasterMaterial>(m_mapMaterial[pMat]);
	}
	FbxSurfacePhong* pSrfPhong = (FbxSurfacePhong*)pMat;
	int nProp = pMat->GetSrcPropertyCount();
	FbxProperty pProp = pSrfPhong->GetFirstProperty();


	shared_ptr<RasterMaterial> pMatRes = ResourceManager<MaterialResource>::GetInstance()->CreateResource<RasterMaterial>(m_fileDir + pMat->GetName() + ".smat.xml");
	m_mapMaterial[pMat] = pMatRes;

	while (pProp.IsValid())
	{
		//std::cout << pProp.GetName() << std::endl;
		pProp = pMat->GetNextProperty(pProp);
		int nTextureCount = pProp.GetSrcObjectCount<FbxFileTexture>();
		for (int i = 0; i < nTextureCount; ++i)
		{
			FbxFileTexture* pTex = pProp.GetSrcObject<FbxFileTexture>(i);
			std::cout <<pProp.GetName()<<":"<< getFileName(pTex->GetName()).c_str() << std::endl;

			string strProperty = pProp.GetName();
			string fileName = getFileName(pTex->GetName());

			if (_tcsstr(strProperty.c_str(), "Diffuse") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(m_fileDir + fileName);

			}
			else if (_tcsstr(strProperty.c_str(), "Specular") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(m_fileDir + fileName);
			}
			else if (_tcsstr(strProperty.c_str(), "Normal") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(m_fileDir + fileName);
			}
			else if (_tcsstr(strProperty.c_str(), "Emissive") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(m_fileDir + fileName);
			}
		}
	}
	return pMatRes;
	
}
