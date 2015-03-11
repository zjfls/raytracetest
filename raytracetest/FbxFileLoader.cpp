#include "stdafx.h"
#include "FbxFileLoader.h"
#include "FbxAsset.h"
#include "FbxAppManager.h"
#include "ResourceMananger.h"
#include "MeshResource.h"

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
	FbxNode* pRootNode = pAsset->m_pFbxScene->GetRootNode();
	if (pRootNode == nullptr)
	{
		return pAsset;
	}
	ProcessNode(pRootNode, path);
	//
	return pAsset;
}

void FbxFileLoader::ProcessNode(FbxNode* pNode, string refPath)
{
	refPath = refPath + "/" + pNode->GetName();
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();
	std::cout << " " << pNode->GetName() << std::endl;
	//
	int nMaterialCount = pNode->GetMaterialCount();
	for (int i = 0; i < nMaterialCount; ++i)
	{
		FbxSurfaceMaterial* pMat = pNode->GetMaterial(i);
		int nPropertyCount = pMat->GetSrcPropertyCount();
		FbxProperty kProp = pMat->GetFirstProperty();
		while (kProp.IsValid() == true)
		{
			int nSrcObjCount = kProp.GetSrcObjectCount();
			for (int j = 0; j < nSrcObjCount; ++j)
			{
				FbxObject* pObj = kProp.GetSrcObject(j);
				pObj->GetUserDataPtr();
			}
		}
	}
	//
	
	if (pAttribute != nullptr)
	{
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::eMesh:
			{

				ProcessMesh(pNode, refPath);
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
		ProcessNode(pChildNode, refPath);
	}
}
struct stNormalPolyIndex
{
	float x, y, z;//normal;
	int triIndex;
};
void FbxFileLoader::ProcessMesh(FbxNode* pNode, string refPath)
{
	if (ResourceMananger<MeshResource>::GetInstance()->GetResource(refPath) != nullptr)
	{
		return;
	}
	shared_ptr<MeshResource> pMeshResource(new MeshResource());
	pMeshResource->m_refPath = refPath;
	ResourceMananger<MeshResource>::GetInstance()->AddResource(refPath, pMeshResource);
	m_pAsset->AddResource(refPath, pMeshResource);
	//
	FbxMesh* pMesh = pNode->GetMesh();
	if (pMesh == nullptr)
	{
		return;
	}
	int triangleCount = pMesh->GetPolygonCount();
	int vertexCounter = 0;
	int cpCount = pMesh->GetControlPointsCount();
	std::vector<int> indexVec;
	std::vector<float> vertexVec;
	std::vector<float> areaVec;//Ãæ»ý
	std::vector<float> normalVec;
	//get vertex pos
	for (int i = 0; i < cpCount; ++i)
	{
		float x, y, z;
		x = pMesh->GetControlPointAt(i).mData[0];
		y = pMesh->GetControlPointAt(i).mData[2];
		z = pMesh->GetControlPointAt(i).mData[1];
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
			std::cout << "by Polygon ref direct!" << std::endl;
			for (int i = 0; i < triangleCount; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					int cpIndex = indexVec[i * 3 + j];
					stNormalPolyIndex np;
					np.triIndex = i;
					np.x = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[0];
					np.y = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[2];
					np.z = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[1];
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
	desc.usedesc = stVertexData::EVertexPosition;
	desc.typedesc = stVertexData::EVertexTypeFloat3;
	desc.nOffset = 0;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset = cpCount * sizeof(float) * 3;
	desc.usedesc = stVertexData::EVertexNormal;
	desc.typedesc = stVertexData::EVertexTypeFloat3;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData.vecDataDesc.push_back(desc);
	nVBOffset += cpCount * sizeof(float) * 3;
	pMeshResource->m_VertexData.nNumVertex = cpCount;
	pMeshResource->m_VertexData.pData = new unsigned char[nVBOffset];
	for (int i = 0; i < pMeshResource->m_VertexData.vecDataDesc.size(); ++i)
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
			case stVertexData::EVertexTypeFloat1:
			{

			}
			break;
			default:
			break;
		}

	}

#pragma endregion
}
