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

void FbxAppManager::ProcessMesh(FbxNode* pNode)
{
	FbxMesh* pMesh = pNode->GetMesh();
	if (pMesh == nullptr)
	{
		return;
	}
	int triangleCount = pMesh->GetPolygonCount();
	int vertexCounter = 0;
	for (int i = 0; i < triangleCount; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int ctrlPointIndex = pMesh->GetPolygonVertex(i, j);
			//std::cout << i << "th triangle:" << j<<"th vertex:";
			//int ctrlPointIndex = pMesh->GetPolygonVertex(i, j);
			//std::cout << " index:" << ctrlPointIndex;
			//FbxVector4* pCtrlPoint = pMesh->GetControlPoints();
			//std::cout << "x=" << pCtrlPoint[ctrlPointIndex].mData[0] << "y=" << pCtrlPoint[ctrlPointIndex].mData[1] << "z=" << pCtrlPoint[ctrlPointIndex].mData[2];
			//std::cout << endl;

			//FbxGeometryElementNormal* pNormal = pMesh->GetPolygonVertexNormal(i, j);

		}
	}
}

