#include "stdafx.h"
#include "FbxAppImporter.h"
#include "FbxAppManager.h"
#include "AssetManager.h"
#include "FbxAsset.h"
#include "SimpleRasterMaterial.h"
#include "MeshResource.h"
#include "Prefab.h"
#include "FilePath.h"
#include "Mesh.h"
#include "tinyxml2.h"
#include <fstream>
using namespace tinyxml2;
FbxAppImporter* Singleton<FbxAppImporter>::_instance = nullptr;

FbxAppImporter::FbxAppImporter()
{
}


FbxAppImporter::~FbxAppImporter()
{
}

void FbxAppImporter::ImportFbxFile(string path)
{
	FbxAsset* pAsset = (FbxAsset*)AssetManager::GetInstance()->LoadAsset("./data/meshes/file_split.fbx");
	string assetDirectory = getFileDirectory(pAsset->m_strPath);
	string assetName = getFileName(pAsset->m_strPath);
	assetName = removeSuffix(assetName);
	std::cout << "asset path:" << assetDirectory.c_str() << std::endl;
	std::cout << "asset name:" << assetName.c_str() << std::endl;
	std::vector<shared_ptr<IResource>> vecRes = pAsset->GetAllResource();
	int nMatIndex = 0;
	int nMeshIndex = 0;
	//build refnamemap
	for each (shared_ptr<IResource> pRes in vecRes)
	{
		shared_ptr<SimpleRasterMaterial> pMat = dynamic_pointer_cast<SimpleRasterMaterial>(pRes);
		if (pMat != nullptr)
		{
			std::cout << "import material:" << pMat->GetRefPath().c_str() << std::endl;
			continue;
		}
		shared_ptr<Prefab>	pPrefab = dynamic_pointer_cast<Prefab>(pRes);
		if (pPrefab != nullptr)
		{
			std::cout << "import prefab:" << pPrefab->GetRefPath().c_str() << std::endl;
			string prefabPath = assetDirectory + assetName + ".prefab.xml";
			//ImportPrefab(pPrefab, prefabPath);
			continue;
		}

		shared_ptr<MeshResource> pMesh = dynamic_pointer_cast<MeshResource>(pRes);
		if (pMesh != nullptr)
		{
			string meshName = getFileName(pMesh->GetRefPath());
			string meshPath = assetDirectory + meshName + ".mesh";
			if (m_refNameMap.find(pMesh->GetRefPath()) == std::end(m_refNameMap))
			{
				m_refNameMap[pMesh->GetRefPath()] = meshPath;
			}
			else
			{
				nMeshIndex++;
				char temp[25];
				_itoa_s(nMeshIndex, temp, 10);
				m_refNameMap[pMesh->GetRefPath()] = assetDirectory + meshName + temp + ".mesh";

			}
			//ImportMesh(pMesh, m_refNameMap[pMesh->GetRefPath()]);
			continue;
		}
	}
	for each (shared_ptr<IResource> pRes in vecRes)
	{
		shared_ptr<SimpleRasterMaterial> pMat = dynamic_pointer_cast<SimpleRasterMaterial>(pRes);
		if (pMat != nullptr)
		{
			continue;
		}
		shared_ptr<Prefab>	pPrefab = dynamic_pointer_cast<Prefab>(pRes);
		if (pPrefab != nullptr)
		{
			ImportPrefab(pPrefab, m_refNameMap[pPrefab->GetRefPath()]);
			continue;
		}

		shared_ptr<MeshResource> pMesh = dynamic_pointer_cast<MeshResource>(pRes);
		if (pMesh != nullptr)
		{
			ImportMesh(pMesh, m_refNameMap[pMesh->GetRefPath()]);
			continue;
		}
	}
	system("pause");
}

void FbxAppImporter::ImportPrefab(shared_ptr<Prefab> pPrefab, string path)
{
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("prefab×ÊÔ´"));
	tinyxml2::XMLElement* root = doc.NewElement("WorldObj");
	doc.LinkEndChild(root);
	PrefabProcessWorldObj(doc,pPrefab->m_pRoot, root);
	doc.SaveFile(path.c_str());
}

void FbxAppImporter::PrefabProcessWorldObj(XMLDocument& doc,IWorldObj* pObj, XMLElement* elem)
{
	if (pObj == nullptr || elem == nullptr)
	{
		return;
	}
	elem->SetAttribute("name", pObj->m_strName.c_str());
	unsigned int nModuleCount = pObj->GetModuleCount();
	for (unsigned int i = 0; i < nModuleCount; ++i)
	{
		ModuleBase* pModule = pObj->GetModule(i);
		Transform* pTrans = dynamic_cast<Transform*>(pModule);
		if (pTrans != nullptr)
		{
			XMLElement* pElemTrans = doc.NewElement("Transform");
			PrefabProcessTransformModule(doc, pTrans, pElemTrans);
			elem->LinkEndChild(pElemTrans);
			continue;
		}
		Mesh* pMesh = dynamic_cast<Mesh*>(pModule);
		if (pMesh != nullptr)
		{
			XMLElement* pElementMesh = doc.NewElement("Mesh");
			PrefabProcessMeshModule(doc, pMesh, pElementMesh);
			elem->LinkEndChild(pElementMesh);
			
			continue;
		}

	}

	unsigned int nChildCount = pObj->GetChildCount();
	for (unsigned int i = 0; i < nChildCount; ++i)
	{
		IWorldObj* pChild = pObj->GetChild(i);
		XMLElement* pChildElem = doc.NewElement("WorldObj");
		elem->LinkEndChild(pChildElem);
		PrefabProcessWorldObj(doc, pChild, pChildElem);
	}
	//for (int i = 0;)
}

void FbxAppImporter::PrefabProcessMeshModule(tinyxml2::XMLDocument& doc, Mesh* pMesh, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("Name", m_refNameMap[pMesh->m_pResource->GetRefPath()].c_str());
}

void FbxAppImporter::PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, Transform* pTrans, tinyxml2::XMLElement* pElem)
{
	Vector3 translate = pTrans->GetLocalTranslate();
	Vector3 scale = pTrans->GetScale();
	Orientation ori = pTrans->GetOrientation();
	XMLElement* pElemT = doc.NewElement("Translation");
	XMLElement* pElemS = doc.NewElement("Scale");
	XMLElement* pElemR = doc.NewElement("Rotation");
	pElem->LinkEndChild(pElemT);
	pElem->LinkEndChild(pElemR);
	pElem->LinkEndChild(pElemS);
	//
	pElemT->SetAttribute("x", translate.m_fx);
	pElemT->SetAttribute("y", translate.m_fy);
	pElemT->SetAttribute("z", translate.m_fz);

	pElemR->SetAttribute("x", ori.m_vecEulerAngle.m_fx);
	pElemR->SetAttribute("y", ori.m_vecEulerAngle.m_fy);
	pElemR->SetAttribute("z", ori.m_vecEulerAngle.m_fz);

	pElemS->SetAttribute("x", scale.m_fx);
	pElemS->SetAttribute("y", scale.m_fy);
	pElemS->SetAttribute("z", scale.m_fz);
	//
}

void FbxAppImporter::PrefabProcessMaterial(tinyxml2::XMLDocument& doc, IMaterial* pMaterial, tinyxml2::XMLElement* pElem)
{

}

void FbxAppImporter::ImportMesh(shared_ptr<MeshResource> pMesh, string path)
{
	std::cout << "save mesh:" << path.c_str() << std::endl;
	if (_access(path.c_str(), 0) != -1)
	{
		if (remove(path.c_str()) != 0)
		{
			std::cout << "remove file failed!" << std::endl;
		}
	}
	FILE* fp;
	errno_t eOpen = fopen_s(&fp, path.c_str(), "wb");
	//fclose(fp);
	//return;
	if (0 != eOpen)
	{
		return;
	}
	int version = 100;
	fwrite((void*)&version, sizeof(int), 1, fp);
	//write index data
	unsigned int nIndexStrip = 2;
	if (pMesh->m_IndexData.indexDesc == stIndexData::EIndexInt)
	{
		nIndexStrip = 1;
	}
	//4×Ö½Ú
	int indexType = (int)pMesh->m_IndexData.indexDesc;
	fwrite((void*)&indexType, sizeof(indexType), 1, fp);

	//
	fwrite((void*)&pMesh->m_IndexData.indexNum, sizeof(int), 1, fp);
	fwrite((void*)pMesh->m_IndexData.pData, nIndexStrip * pMesh->m_IndexData.indexNum, 1, fp);
	//write vertex data
	//write desc data
	unsigned int nVDescNum = pMesh->m_VertexData.vecDataDesc.size();
	fwrite((void*)&nVDescNum, sizeof(unsigned int), 1, fp);
	for (unsigned int i = 0; i < nVDescNum; ++i)
	{
		stVertexData::VertexDataDesc desc = pMesh->m_VertexData.vecDataDesc[i];
		int useDesc, typeDesc;
		useDesc = (int)desc.usedesc;
		typeDesc = (int)desc.typedesc;
		unsigned int nOffset = desc.nOffset;
		fwrite((void*)&useDesc, sizeof(int), 1, fp);
		fwrite((void*)&typeDesc, sizeof(int), 1, fp);
		fwrite((void*)&nOffset, sizeof(unsigned int), 1, fp);
	}
	unsigned int nNumVertex = pMesh->m_VertexData.nNumVertex;
	unsigned int nSizeofVB = pMesh->m_VertexData.GetVertexDataLength() * pMesh->m_VertexData.nNumVertex;
	fwrite((void*)&nSizeofVB, sizeof(unsigned int), 1, fp);
	fwrite(pMesh->m_VertexData.pData, nSizeofVB, 1, fp);
	fclose(fp);
}
