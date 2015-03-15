#include "stdafx.h"
#include "FbxFileLoader.h"
#include "FbxAsset.h"
#include "FbxAppManager.h"
#include "ResourceMananger.h"
#include "MeshResource.h"
#include "Mesh.h"
#include "PrefabResource.h"
IAsset* FbxFileLoader::Load(string path, void* pArg /*= nullptr*/)
{
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
	IWorldObj* pRoot = ProcessNode(pRootNode, path);


	shared_ptr<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->CreateResource();
	pPrefab->m_pRoot = pRoot;
	pAsset->AddResource(pPrefab->GetRefPath(), pPrefab);
	//
	return pAsset;
}

IWorldObj* FbxFileLoader::ProcessNode(FbxNode* pNode, string refPath, IWorldObj* pParent)
{
	refPath = refPath + "/" + pNode->GetName();
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();
	IWorldObj* pObj = new IWorldObj;
	pObj->m_strName = pNode->GetName();
	FbxTransform nodeTrans = pNode->GetTransform();
	FbxDouble3 trans = pNode->LclTranslation.Get();
	FbxDouble3 rot = pNode->LclRotation.Get();
	FbxDouble3 scal = pNode->LclScaling.Get();
	Transform* pTransform = (Transform*)pObj->GetModule(0);
	pTransform->SetTranslate(trans.mData[0], trans.mData[2], trans.mData[1]);
	pTransform->SetScale(scal.mData[0], scal.mData[2], scal.mData[1]);
	pTransform->SetOrientation(rot.mData[0], rot.mData[2], rot.mData[1]);


	if (pAttribute != nullptr)
	{
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::eMesh:
			{

				shared_ptr<MeshResource> pRes = ProcessMesh(pNode, refPath,pObj);
				Mesh* pMesh = pObj->addModule<Mesh>();
				pMesh->m_pResource = pRes;
			}
			break;
			default:
			break;
		}
	}
	int nChild = pNode->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		FbxNode* pChildNode = pNode->GetChild(i);
		IWorldObj* pChild = ProcessNode(pChildNode, refPath);
		pObj->addChild(pChild);
	}
	return pObj;
}
struct stNormalPolyIndex
{
	float x, y, z;//normal;
	int triIndex;
};
shared_ptr<MeshResource> FbxFileLoader::ProcessMesh(FbxNode* pNode, string refPath, IWorldObj* obj)
{
	if (ResourceManager<MeshResource>::GetInstance()->GetResource(refPath) != nullptr)
	{
		return nullptr;
	}
	shared_ptr<MeshResource> pMeshResource = ResourceManager<MeshResource>::GetInstance()->CreateResource(refPath);
	m_pAsset->AddResource(refPath, pMeshResource);
	//
 	FbxMesh* pMesh = pNode->GetMesh();

	if (pMesh == nullptr)
	{
		return nullptr;
	}
	int triangleCount = pMesh->GetPolygonCount();
	int vertexCounter = 0;
	int cpCount = pMesh->GetControlPointsCount();
	std::vector<int> indexVec;
	std::vector<float> vertexVec;
	std::vector<float> areaVec;//Ãæ»ý
	std::vector<float> normalVec;
	std::vector<float> uvVec;
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
			for (int i = 0; i < indexVec.size(); ++i)
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
				u = pLayerUV->GetDirectArray().GetAt(index).mData[0];
				v = pLayerUV->GetDirectArray().GetAt(index).mData[1];
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
#pragma region AddMeshResource
	stIndexData::EnumIndexDesc eIndexDesc = stIndexData::EIndexInt;
	int nIndexLength = indexVec.size();
	if (nIndexLength <= 65535)
	{
		eIndexDesc = stIndexData::EIndexShort;
	}
	void* pTemp = nullptr;
	if (eIndexDesc == stIndexData::EIndexInt)
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
	else if (eIndexDesc == stIndexData::EIndexShort)
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
	stVertexData::VertexDataDesc desc;
	//
	desc.usedesc = stVertexData::EVertexPosition;
	desc.typedesc = stVertexData::EVertexTypeFloat3;
	desc.nOffset = 0;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset = cpCount * sizeof(float) * 3;
	//
	desc.usedesc = stVertexData::EVertexNormal;
	desc.typedesc = stVertexData::EVertexTypeFloat3;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(float) * 3;
	//
	desc.usedesc = stVertexData::EVertexUV;
	desc.typedesc = stVertexData::EVertexTypeFloat2;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(float) * 2;
	//
	pMeshResource->m_VertexData.nNumVertex = cpCount;
	pMeshResource->m_VertexData.pData = new unsigned char[nVBOffset];
	for (unsigned int i = 0; i < pMeshResource->m_VertexData.vecDataDesc.size(); ++i)
	{
		stVertexData::VertexDataDesc desc = pMeshResource->m_VertexData.vecDataDesc[i];
		void* pTempVoid = (unsigned char*)pMeshResource->m_VertexData.pData + desc.nOffset;
		switch (desc.typedesc)
		{
			case stVertexData::EVertexTypeFloat3:
			{
				float* pFloat = (float*)pTempVoid;
				for (int j = 0; j < cpCount; ++j)
				{
					if (pMeshResource->m_VertexData.vecDataDesc[i].usedesc == stVertexData::EVertexPosition)
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
					else if (pMeshResource->m_VertexData.vecDataDesc[i].usedesc == stVertexData::EVertexNormal)
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
			case stVertexData::EVertexTypeFloat2:
			{
				float* pFloat = (float*)pTempVoid;
				for (int j = 0; j < cpCount; ++j)
				{
					switch (pMeshResource->m_VertexData.vecDataDesc[i].usedesc)
					{
						case stVertexData::EVertexUV:
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
			case stVertexData::EVertexTypeFloat1:
			{

			}
			break;
			default:
			break;
		}

	}
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
		shared_ptr<MeshResource> pSubMesh = ResourceManager<MeshResource>::GetInstance()->CreateResource(refPath);// (new MeshResource);
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
		for each (stVertexData::VertexDataDesc desc in pSubMesh->m_VertexData.vecDataDesc)
		{
			int nElementLength = pSubMesh->m_VertexData.GetTypeLength(desc);

			for (int i = 0; i < pSubMesh->m_VertexData.nNumVertex; ++i)
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
		if (pSubMesh->m_IndexData.indexDesc == stIndexData::EIndexShort)
		{
			pSubMesh->m_IndexData.pData = (void*)new unsigned char[subIndexVec.size() * sizeof(short)];
			short* pShortData = (short*)pSubMesh->m_IndexData.pData;
			for each (int index in subIndexVec)
			{
				*pShortData = index;
				pShortData++;
			}
		}
		else if (pSubMesh->m_IndexData.indexDesc == stIndexData::EIndexInt)
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
