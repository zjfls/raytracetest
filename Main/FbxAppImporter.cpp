#include "stdafx.h"
#include "FbxAppImporter.h"
#include "FbxAppManager.h"
#include "AssetManager.h"
#include "FbxAsset.h"
#include "MeshResource.h"
#include "PrefabResource.h"
#include "FilePath.h"
#include "Mesh.h"
#include "tinyxml2.h"
#include <fstream>
#include "SkeletonResource.h"
#include "skeleton.h"
#include "TextureSampler.h"
#include "Texture.h"
#include "RasterMaterial.h"
#include "IWorldObj.h"
#include <io.h>
#include "SkeletonObj.h"
#include "AnimationTrack.h"
#include "MaterialPass.h"
#include "VertexShader.h"
#include "FragShader.h"
using namespace tinyxml2;
using tinyxml2::XMLDocument;
template  class MAIN_API  Singleton<FbxAppImporter>;
template<> SmartPointer<FbxAppImporter> Singleton<FbxAppImporter>::_instance = nullptr;

FbxAppImporter::FbxAppImporter()
{
}


FbxAppImporter::~FbxAppImporter()
{
}

void FbxAppImporter::ImportFbxFile(std::string path)
{
	//SmartPointer<IWorldObj> pWorldObj;
	//int refCount = pWorldObj.use_count();
	//{
	//	pWorldObj = SmartPointer<IWorldObj>(new IWorldObj);
	//	refCount = pWorldObj.use_count();
	//}
	//{
	//	SmartPointer<IWorldObj> pWorldObj2 = pWorldObj;
	//	IWorldObj* pObj = pWorldObj.get();
	//	refCount = pWorldObj.use_count();
	//	SmartPointer<IWorldObj> pWorldObj3(pObj);
	//	refCount = pWorldObj.use_count();
	//	int i = 0;
	//}
	//refCount = pWorldObj.use_count();
	FbxAsset* pAsset = (FbxAsset*)AssetManager::GetInstance()->LoadAsset(path);
	std::string assetDirectory = getFileDirectory(pAsset->m_strPath);
	std::string assetName = getFileName(pAsset->m_strPath);
	assetName = removeSuffix(assetName);
	std::cout << "asset path:" << assetDirectory.c_str() << std::endl;
	std::cout << "asset name:" << assetName.c_str() << std::endl;
	std::vector<SmartPointer<IResource>> vecRes = pAsset->GetAllResource();
	int nMatIndex = 0;
	int nMeshIndex = 0;
	////build refnamemap
	//for each (SmartPointer<IResource> pRes in vecRes)
	//{
	//	SmartPointer<SimpleRasterMaterial> pMat = dynamic_pointer_cast<SimpleRasterMaterial>(pRes);
	//	if (pMat != nullptr)
	//	{
	//		std::cout << "import material:" << pMat->GetRefPath().c_str() << std::endl;
	//		continue;
	//	}
	//	SmartPointer<PrefabResource>	pPrefab = dynamic_pointer_cast<PrefabResource>(pRes);
	//	if (pPrefab != nullptr)
	//	{
	//		
	//		std::cout << "import prefab:" << pPrefab->GetRefPath().c_str() << std::endl;
	//		string prefabPath = assetDirectory + assetName + ".prefab.xml";
	//		//ImportPrefab(pPrefab, prefabPath);
	//		m_refNameMap[pPrefab->GetRefPath()] = prefabPath;
	//		continue;
	//	}

	//	SmartPointer<MeshResource> pMesh = dynamic_pointer_cast<MeshResource>(pRes);
	//	if (pMesh != nullptr)
	//	{
	//		string meshName = getFileName(pMesh->GetRefPath());
	//		string meshPath = assetDirectory + meshName + ".mesh";
	//		if (m_refNameMap.find(pMesh->GetRefPath()) == std::end(m_refNameMap))
	//		{
	//			m_refNameMap[pMesh->GetRefPath()] = meshPath;
	//		}
	//		else
	//		{
	//			nMeshIndex++;
	//			char temp[25];
	//			_itoa_s(nMeshIndex, temp, 10);
	//			m_refNameMap[pMesh->GetRefPath()] = assetDirectory + meshName + temp + ".mesh";

	//		}
	//		//ImportMesh(pMesh, m_refNameMap[pMesh->GetRefPath()]);
	//		continue;
	//	}
	//}
	for each (SmartPointer<IResource> pRes in vecRes)
	{
		SmartPointer<RasterMaterial> pMat = pRes.SmartPointerCast<RasterMaterial>();
		if (pMat != nullptr)
		{
			ImportMaterial(pMat, pMat->GetRefPath());
			continue;
		}
		SmartPointer<PrefabResource>	pPrefab = pRes.SmartPointerCast<PrefabResource>();
		if (pPrefab != nullptr)
		{
			ImportPrefab(pPrefab, pPrefab->GetRefPath());
			continue;
		}

		SmartPointer<MeshResource> pMesh = pRes.SmartPointerCast<MeshResource>();
		if (pMesh != nullptr)
		{
			ImportMesh(pMesh, pMesh->GetRefPath());
			continue;
		}

		SmartPointer<SkeletonResource> pSkeRes = pRes.SmartPointerCast<SkeletonResource>();
		if (pSkeRes != nullptr)
		{
			ImportSkeleton(pSkeRes, pSkeRes->GetRefPath());
		}
	}
	//system("pause");
}

void FbxAppImporter::ImportPrefab(SmartPointer<PrefabResource> pPrefab, std::string path)
{
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("prefab resource"));
	tinyxml2::XMLElement* root = doc.NewElement("WorldObj");
	doc.LinkEndChild(root);
	PrefabProcessWorldObj(doc,pPrefab->m_pRoot, root);
	doc.SaveFile(path.c_str());
}

void FbxAppImporter::PrefabProcessWorldObj(XMLDocument& doc,SmartPointer<IWorldObj> pObj, XMLElement* elem)
{
	if (pObj == nullptr || elem == nullptr)
	{
		return;
	}
	elem->SetAttribute("name", pObj->m_strName.c_str());
	unsigned int nModuleCount = pObj->GetModuleCount();
	for (unsigned int i = 0; i < nModuleCount; ++i)
	{
		SmartPointer<ModuleBase> pModule = pObj->GetModule(i);
		SmartPointer<Transform> pTrans = pModule.SmartPointerCast<Transform>();
		if (pTrans != nullptr)
		{
			XMLElement* pElemTrans = doc.NewElement("Transform");
			PrefabProcessTransformModule(doc, pTrans, pElemTrans);
			elem->LinkEndChild(pElemTrans);
			continue;
		}
		SmartPointer<Mesh> pMesh = pModule.SmartPointerCast<Mesh>();
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
		SmartPointer<IWorldObj> pChild = pObj->GetChild(i);
		XMLElement* pChildElem = doc.NewElement("WorldObj");
		elem->LinkEndChild(pChildElem);
		PrefabProcessWorldObj(doc, pChild, pChildElem);
	}
	//for (int i = 0;)
}

void FbxAppImporter::PrefabProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMesh->GetMeshResource()->GetRefPath().c_str());
	if (pMesh->m_pSharedMaterial == nullptr)
	{
		return;
	}
	XMLElement* pMatElem = doc.NewElement("Material");
	pElem->LinkEndChild(pMatElem);
	//pMatElem->SetAttribute("Name", "testmat");
	PrefabProcessMaterial(doc, pMesh->m_pSharedMaterial.SmartPointerCast<RasterMaterial>(), pMatElem);
}

void FbxAppImporter::PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem)
{
	Vector3 translate = pTrans->GetLocalTranslate();
	Vector3 scale = pTrans->GetScale();
	Vector3 rotation = pTrans->GetRotation();
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

	pElemR->SetAttribute("x", rotation.m_fx);
	pElemR->SetAttribute("y", rotation.m_fy);
	pElemR->SetAttribute("z", rotation.m_fz);

	pElemS->SetAttribute("x", scale.m_fx);
	pElemS->SetAttribute("y", scale.m_fy);
	pElemS->SetAttribute("z", scale.m_fz);
	//
}

void FbxAppImporter::PrefabProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMaterial->GetRefPath().c_str());
	for each (std::pair<std::string, MaterialArg*> pair in pMaterial->m_matArgs)
	{
		switch (pair.second->m_EType)
		{
			case EMATARGTYPESAMPLER:
			{
				//XMLElement* pElemSamp = doc.NewElement("Sampler");
				//pElemSamp->SetAttribute("Name", pair.first.c_str());

				//TextureSampler* pTexSampler = pair.second->GetData<TextureSampler>();
				//pElemSamp->SetAttribute("Ref", pTexSampler->m_pTexture->GetRefPath().c_str());
				//pElem->LinkEndChild(pElemSamp);
			}
			break;
			default:
			break;
		}
	}
}

void FbxAppImporter::ImportMesh(SmartPointer<MeshResource> pMesh, std::string path)
{
	//
	//pMesh->m_VertexData->ComputeTangent(*pMesh->m_IndexData);
	//
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
	if (0 != eOpen)
	{
		return;
	}

	//write version
	int version = 100;
	fwrite((void*)&version, sizeof(int), 1, fp);
	//write index data
	unsigned int nIndexStrip = 2;
	if (pMesh->m_IndexData->indexDesc == EIndexInt)
	{
		nIndexStrip = 1;
	}
	//4�ֽ� write indexdesc
	int indexType = (int)pMesh->m_IndexData->indexDesc;
	fwrite((void*)&indexType, sizeof(indexType), 1, fp);

	//index number
	fwrite((void*)&pMesh->m_IndexData->indexNum, sizeof(int), 1, fp);
	//index value
	fwrite((void*)pMesh->m_IndexData->pData, nIndexStrip * pMesh->m_IndexData->indexNum, 1, fp);
	//write vertex data
	//write desc data
	unsigned int nVDescNum = pMesh->m_VertexData->vecDataDesc.size();
	fwrite((void*)&nVDescNum, sizeof(unsigned int), 1, fp);
	for (unsigned int i = 0; i < nVDescNum; ++i)
	{
		VertexData::VertexDataDesc desc = pMesh->m_VertexData->vecDataDesc[i];
		int useDesc, typeDesc;
		useDesc = (int)desc.usedesc;
		typeDesc = (int)desc.typedesc;
		unsigned int nOffset = desc.nOffset;
		fwrite((void*)&useDesc, sizeof(int), 1, fp);
		fwrite((void*)&typeDesc, sizeof(int), 1, fp);
		fwrite((void*)&nOffset, sizeof(unsigned int), 1, fp);
	}
	unsigned int nNumVertex = pMesh->m_VertexData->m_nNumVertex;
	unsigned int nSizeofVB = pMesh->m_VertexData->GetVertexDataLength() * pMesh->m_VertexData->m_nNumVertex;
	fwrite((void*)&nSizeofVB, sizeof(unsigned int), 1, fp);
	fwrite(pMesh->m_VertexData->pData, nSizeofVB, 1, fp);
	fclose(fp);
}

void FbxAppImporter::ImportSkeleton(SmartPointer<SkeletonResource> pSkeRes, std::string path)
{
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("skeleton resource"));
	tinyxml2::XMLElement* pSkeInfo = doc.NewElement("Info");
	pSkeInfo->SetAttribute("BoneNum", pSkeRes->m_nBoneNum);
	doc.LinkEndChild(pSkeInfo);
	tinyxml2::XMLElement* pBoneRoot = doc.NewElement("Bone");
	doc.LinkEndChild(pBoneRoot);
	//PrefabProcessWorldObj(doc, pPrefab->m_pRoot, root);
	SkeletonProcessBone(doc, pSkeRes->m_pRoot, pBoneRoot);
	doc.SaveFile(path.c_str());
}

void FbxAppImporter::SkeletonProcessBone(tinyxml2::XMLDocument& doc, Bone* pBone, tinyxml2::XMLElement* pElem)
{
	if (pBone == nullptr && pElem == nullptr)
	{
		return;
	}
	pElem->SetAttribute("Name", pBone->m_strName.c_str());
	Vector3 t, r, s;
	t = pBone->t;
	r = pBone->r;
	s = pBone->s;
	XMLElement* pElemT = doc.NewElement("Translation");
	XMLElement* pElemS = doc.NewElement("Scale");
	XMLElement* pElemR = doc.NewElement("Rotation");
	pElem->LinkEndChild(pElemT);
	pElem->LinkEndChild(pElemR);
	pElem->LinkEndChild(pElemS);

	pElemT->SetAttribute("x", t.m_fx);
	pElemT->SetAttribute("y", t.m_fy);
	pElemT->SetAttribute("z", t.m_fz);

	pElemR->SetAttribute("x", r.m_fx);
	pElemR->SetAttribute("y", r.m_fy);
	pElemR->SetAttribute("z", r.m_fz);

	pElemS->SetAttribute("x", s.m_fx);
	pElemS->SetAttribute("y", s.m_fy);
	pElemS->SetAttribute("z", s.m_fz);

	for each (Bone* pChildBone in pBone->vecChild)
	{
		tinyxml2::XMLElement* pChild = doc.NewElement("Bone");
		pElem->LinkEndChild(pChild);
		SkeletonProcessBone(doc, pChildBone, pChild);
	}

}

void FbxAppImporter::ImportMaterial(SmartPointer<RasterMaterial> pMatRes, std::string path)
{
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("material resource"));
	tinyxml2::XMLElement* root = doc.NewElement("Material");
	doc.LinkEndChild(root);
	//PrefabProcessWorldObj(doc, pPrefab->m_pRoot, root);
	root->SetAttribute("Name", removeSuffix(getFileName(pMatRes->GetRefPath())).c_str());
	for each (std::pair<std::string, MaterialArg*> p in pMatRes->m_matArgs)
	{
		XMLElement* pArgElem = doc.NewElement("MaterialArg");
		pArgElem->SetAttribute("Name", p.first.c_str());
		root->LinkEndChild(pArgElem);
		switch (p.second->m_EType)
		{
			case EMATARGTYPESAMPLER:
			{
				pArgElem->SetAttribute("Type", "TextureSampler");
				XMLElement* pTextureElem = doc.NewElement("Texture");
				pArgElem->LinkEndChild(pTextureElem);
				TextureSampler* pSampler = p.second->GetData<TextureSampler>();
				pTextureElem->SetAttribute("RefPath",pSampler->m_pTexture->GetRefPath().c_str() );
				switch (pSampler->m_pTexture->GetTexType())
				{
					case ETEXTYPE2D:
					{
						pTextureElem->SetAttribute("Type", "Texture2D");
					}
					break;
					default:
					{
						pTextureElem->SetAttribute("Type", "Invalid");
					}
					break;
				}
			}
			break;
			default:
			break;
		}

		
	}
	//pass
	//
	XMLElement* pPass = doc.NewElement("RenderPass");
	root->InsertEndChild(pPass);
	XMLElement* pVertShader = doc.NewElement("VertexShader");
	XMLElement* pFragShader = doc.NewElement("FragElem");
	pPass->SetAttribute("Name", "bladesouldefault");
	pPass->SetAttribute("BRDF", "BlinPhong");
	pPass->InsertEndChild(pVertShader);
	pPass->InsertEndChild(pFragShader);
	pVertShader->SetAttribute("refPath", "./data/shader/VertexStandard.vsm");
	pVertShader->SetAttribute("ShaderType", "Origin");
	pFragShader->SetAttribute("refPath", "./data/shader/FragSpec.fsm");
	pVertShader->SetAttribute("ShaderType", "Origin");
	pFragShader->SetAttribute("ShaderType", "Origin");
	doc.SaveFile(path.c_str());
}
