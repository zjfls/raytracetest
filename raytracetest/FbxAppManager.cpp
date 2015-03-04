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

//for blend normal
struct stPolyAndNormal
{
	int polyindex;
	float x, y, z;
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
	std::cout << "control point count" << pMesh->GetControlPointsCount() << std::endl;
	int nCPCount = pMesh->GetControlPointsCount();
	std::vector<float> vertexBuff;
	std::vector<float> normalBuff;
	std::vector<float> vertexS;
	std::vector<int> indexBuff;
	for (int i = 0; i < nCPCount; ++i)
	{
		float x, y, z;
		x = pMesh->GetControlPointAt(i).mData[0];
		y = pMesh->GetControlPointAt(i).mData[1];
		z = pMesh->GetControlPointAt(i).mData[2];
		vertexBuff.push_back(x);
		vertexBuff.push_back(y);
		vertexBuff.push_back(z);
		//float fp = (x + y + z) * 0.5f;
		//float fs = sqrt(fp*(fp - x)*(fp - y)*(fp - z));
		//vertexS.push_back(fs);
	}
	for (int i = 0; i < pMesh->GetPolygonCount(); ++i)
	{
		int x, y, z;
		x = pMesh->GetPolygonVertex(i, 0);
		y = pMesh->GetPolygonVertex(i, 1);
		z = pMesh->GetPolygonVertex(i, 2);
		indexBuff.push_back(x);
		indexBuff.push_back(y);
		indexBuff.push_back(z);


		Vector3 vx, vy, vz;
		vx.m_fx = pMesh->GetControlPointAt(x).mData[0];
		vx.m_fy = pMesh->GetControlPointAt(x).mData[1];
		vx.m_fz = pMesh->GetControlPointAt(x).mData[2];

		vy.m_fx = pMesh->GetControlPointAt(y).mData[0];
		vy.m_fy = pMesh->GetControlPointAt(y).mData[1];
		vy.m_fz = pMesh->GetControlPointAt(y).mData[2];


		vz.m_fx = pMesh->GetControlPointAt(z).mData[0];
		vz.m_fy = pMesh->GetControlPointAt(z).mData[1];
		vz.m_fz = pMesh->GetControlPointAt(z).mData[2];

	}

	FbxLayerElementNormal* pNormal = pMesh->GetElementNormal(0);
	FbxLayerElement::EMappingMode mode = pNormal->GetMappingMode();


	std::cout << "normal count:" << pNormal->GetDirectArray().GetCount() << std::endl;
	switch (pNormal->GetMappingMode())
	{
		case FbxLayerElement::eByControlPoint:
		{
			std::cout<<"normal by control point"<<std::endl;
			switch (pNormal->GetReferenceMode())
			{
				case FbxLayerElement::eDirect:
				{
					std::cout<<"eDirect"<<std::endl;
				}
				break;
				case FbxLayerElement::eIndexToDirect:
				{
					std::cout<<"eIndexToDirect"<<std::endl;
				}
				break;
			default:
				break;
			}
		}
		break;
		case FbxLayerElement::eByPolygonVertex:
		{
			std::cout<<"normal by polygon vertex"<<std::endl;
			switch (pNormal->GetReferenceMode())
			{
				case FbxLayerElement::eDirect:
				{
					std::cout<<"eDirect"<<std::endl;


					std::map<int,std::vector<stPolyAndNormal>> polyAndNormalMap;
					for (int i = 0; i < pMesh->GetPolygonCount(); ++i)
					{
						for (int j = 0; j < 3; ++j)
						{
							int nIndex = pMesh->GetPolygonVertex(i, j);
							stPolyAndNormal polyNormal;
							polyNormal.polyindex = i;
							polyNormal.x = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[0];
							polyNormal.y = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[1];
							polyNormal.z = pNormal->GetDirectArray().GetAt(i * 3 + j).mData[2];
							if (polyAndNormalMap.find(nIndex) != polyAndNormalMap.end())
							{
								polyAndNormalMap[nIndex].push_back(polyNormal);
							}
							else
							{
								std::vector<stPolyAndNormal> vecPolyNormal;
								vecPolyNormal.push_back(polyNormal);
								polyAndNormalMap[nIndex] = vecPolyNormal;
							}
						}
					}
					for (int i = 0; i < nCPCount; ++i)
					{
						float fSum = 0;
						Vector3 v = Vector3::ZERO;
						for_each(std::begin(polyAndNormalMap[i]), std::end(polyAndNormalMap[i]), [&](stPolyAndNormal& pn)
						{
							fSum += vertexS[pn.polyindex]; 
						}
						);
						for_each(std::begin(polyAndNormalMap[i]), std::end(polyAndNormalMap[i]), [&](stPolyAndNormal& pn)
						{
							v = v + Vector3(pn.x,pn.y,pn.z) * vertexS[pn.polyindex]  * (1 / fSum);
							normalBuff.push_back(v.m_fx);
							normalBuff.push_back(v.m_fy);
							normalBuff.push_back(v.m_fz);
							std::cout << "normal:" << v.m_fx << " " << v.m_fy << " " << v.m_fz << std::endl;
						});
					}
				}
				break;
				case FbxLayerElement::eIndexToDirect:
				{
					std::cout<<"eIndexToDirect"<<std::endl;
				}
				break;
			default:
				break;
			}
		}
		break;
	}

	system("pause");
}

