#include "stdafx.h"
#include "FbxAppManager.h"
FbxAppManager* Singleton<FbxAppManager>::_instance = nullptr;

FbxAppManager::FbxAppManager()
{
}


FbxAppManager::~FbxAppManager()
{
	if (m_pFbxScene != nullptr)
	{
		m_pFbxScene->Destroy(true);
		m_pFbxScene = nullptr;
	}
	if (m_pFbxSdkManager != nullptr)
	{
		m_pFbxSdkManager->Destroy();
		m_pFbxSdkManager = nullptr;
	}
}



void FbxAppManager::testFbxLoad()
{
	FbxImporter* pImporter = FbxImporter::Create(m_pFbxSdkManager, "");
	const char* fileName = "file.fbx";

	bool bImportStatus = pImporter->Initialize(fileName, -1, m_pFbxSdkManager->GetIOSettings());
	int nFileMajor, nFileMinor, nFileRevision;
	pImporter->GetFileVersion(nFileMajor, nFileMinor, nFileRevision);
	//bool bImportStatus = pImporter->Initialize(fileName, -1, m_pFbxSdkManager->GetIOSettings());
	if (bImportStatus == false)
	{
		return;
	}
	m_pFbxScene->Clear();
	bImportStatus = pImporter->Import(m_pFbxScene);
	pImporter->Destroy();
	FbxNode* pRootNode = m_pFbxScene->GetRootNode();
	if (pRootNode == nullptr)
	{
		return;
	}
	ProcessNode(pRootNode);
	return;
}

//
void FbxAppManager::ProcessNode(FbxNode* pNode)
{
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();
	if (pAttribute != nullptr)
	{
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::eMesh:
			{
				ProcessMesh(pNode);
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
		ProcessNode(pChildNode);
	}


}

bool FbxAppManager::Init()
{
	if (m_pFbxSdkManager != nullptr)
	{
		m_pFbxSdkManager->Destroy();
	}
	m_pFbxSdkManager = FbxManager::Create();
	if (m_pFbxSdkManager == nullptr)
	{
		return false;
	}


	FbxIOSettings* pIoSetting = FbxIOSettings::Create(m_pFbxSdkManager,IOSROOT);
	m_pFbxSdkManager->SetIOSettings(pIoSetting);


	FbxString lPath = FbxGetApplicationDirectory();
	m_pFbxSdkManager->LoadPluginsDirectory(lPath.Buffer());


	//
	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	m_pFbxScene = FbxScene::Create(m_pFbxSdkManager, "My Scene");
	if (!m_pFbxScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		//exit(1);
	}
	testFbxLoad();
	return true;

}
struct stNormalPolyIndex
{
	float x, y, z;//normal;
	int triIndex;
};
void FbxAppManager::ProcessMesh(FbxNode* pNode)
{
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
		y = pMesh->GetControlPointAt(i).mData[1];
		z = pMesh->GetControlPointAt(i).mData[2];
		vertexVec.push_back(x);
		vertexVec.push_back(y);
		vertexVec.push_back(z);
	}
	//get index Buff
	for (int i = 0; i < triangleCount; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int ctrlPointIndex = pMesh->GetPolygonVertex(i, j);
			indexVec.push_back(ctrlPointIndex);
		}
	}
	//compute area
	//if (pMesh->GetElementNormal(0)->RemapIndexTo(FbxLayerElement::EMappingMode::eByControlPoint) != 1)
	//{
	//	std::cout << "remap failed:" << std::endl;
	//}
	for (int i = 0; i < triangleCount; ++i)
	{
		Vector3 v0, v1, v2;
		int index0, index1, index2;
		index0 = indexVec[i * 3 + 0];
		index1 = indexVec[i * 3 +1];
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
	//get normal
	FbxLayerElementNormal* pNormal = pMesh->GetElementNormal(0);
	switch (pNormal->GetMappingMode())
	{
		case FbxLayerElement::eByControlPoint:
		{
			switch(pNormal->GetReferenceMode())
			{
				case FbxLayerElement::eDirect:
				{

				}
				break;
				case FbxLayerElement::eIndexToDirect:
				{

				}
				break;
			}
		}
		break;
		case FbxLayerElement::eByPolygonVertex:
		{
			switch(pNormal->GetReferenceMode())
			{
				case FbxLayerElement::eDirect:
				{
					std::map<int, std::vector<stNormalPolyIndex>> cpNormalIndexMap;
					std::cout<<"by Polygon ref direct!"<<std::endl;
					for (int i = 0; i < triangleCount; ++i)
					{
						for (int j = 0; j < 3; ++j)
						{
							int cpIndex = indexVec[i * 3 + j];
							stNormalPolyIndex np;
							np.triIndex = i;
							np.x = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[0];
							np.y = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[1];
							np.z = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[2];
							cpNormalIndexMap[cpIndex].push_back(np);
						}
					}
					for (int i = 0; i < cpCount; ++i)
					{
						float fAreaSum;
						for_each(std::begin(cpNormalIndexMap[i]), std::end(cpNormalIndexMap[i]), [&](stNormalPolyIndex& npi)
						{
							fAreaSum += areaVec[npi.triIndex];
						}
						);
						Vector3 vecNormal;
						for_each(std::begin(cpNormalIndexMap[i]), std::end(cpNormalIndexMap[i]), [&](stNormalPolyIndex& npi)
						{
							vecNormal = vecNormal + Vector3(npi.x, npi.y, npi.z) * (areaVec[npi.triIndex] / fAreaSum);
						}
						);
						normalVec.push_back(vecNormal.m_fx);
						normalVec.push_back(vecNormal.m_fy);
						normalVec.push_back(vecNormal.m_fz);
					}
				}
				break;
				case FbxLayerElement::eIndexToDirect:
				{

				}
				break;
			}
		}
		break;
	}

	system("pause");
}

