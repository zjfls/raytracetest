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
//
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
	SmartPointer<IWorldObj> pRoot = ProcessNode(pRootNode, path, nullptr, nullptr);


	SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->CreateResource<PrefabResource>(strPrefabPath + name + ".prefab.xml");
	pPrefab->m_pRoot = pRoot;
	pAsset->AddResource(m_fileDir + name + ".prefab.xml", pPrefab.get());
	pRoot->m_strName = getFileNameWithoutSuffix(path);


	FbxAnimStack* pAniStack = pAsset->m_pFbxScene->GetCurrentAnimationStack();
	if (pAniStack != nullptr)
	{
		std::cout << "find Stack:"<<pAniStack->GetName() << std::endl;
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
			if (m_SkeletonToFbxNode.size() > 0)
			{
				char temp[10];
				_itoa_s(i, temp, 10, 10);
				aniName = aniName + temp;
			}
			std::string refPath = getFileDirectory(path) + aniName + ".animation.xml";
			AnimationResource* pAniRes = ResourceManager<AnimationResource>::GetInstance()->CreateResource<AnimationResource>(aniName).get();
			for each (FbxNode* pNode in p.second)
			{
				
				FbxAnimCurve* pAniCurveTX = pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X);
				if (pAniCurveTX == nullptr)
				{
					break;
				}
				FbxAnimCurve* pAniCurveTY = pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				FbxAnimCurve* pAniCurveTZ = pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				FbxAnimCurve* pAniCurveRX = pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X);
				FbxAnimCurve* pAniCurveRY = pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				FbxAnimCurve* pAniCurveRZ = pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				FbxAnimCurve* pAniCurveSX = pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X);
				FbxAnimCurve* pAniCurveSY = pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				FbxAnimCurve* pAniCurveSZ = pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z);

				AnimationCurve<stTransformData>* pTransCurve = new AnimationCurve<stTransformData>(EANITRANSFORM);
				for (int i = 0; i < pAniCurveTX->KeyGetCount(); ++i)
				{
					KeyFrame<stTransformData> kf;
					FbxAnimCurveKey key = pAniCurveTX->KeyGet(i);
					float fTime = key.GetTime().GetSecondDouble();
					float fValueTX = key.GetValue();
					kf.m_fTime = fTime;
					kf.m_KeyFrameData.m_vecTranslate.m_fx = fValueTX;
					//
					kf.m_KeyFrameData.m_vecTranslate.m_fy = pAniCurveTY->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecTranslate.m_fz = pAniCurveTZ->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecRotation.m_fx = pAniCurveRX->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecRotation.m_fy = pAniCurveRY->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecRotation.m_fz = pAniCurveRZ->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecScale.m_fx = pAniCurveSX->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecScale.m_fy = pAniCurveSY->KeyGet(i).GetValue();
					kf.m_KeyFrameData.m_vecScale.m_fz = pAniCurveSZ->KeyGet(i).GetValue();
					pTransCurve->AddKeyFrame(fTime, kf.m_KeyFrameData);


				}
				pAniRes->m_mapCurves[pNode->GetName()] = pTransCurve;
				//std::cout << "add curve:" << pNode->GetName() << std::endl;
			}
			//
			m_pAsset->AddResource(refPath, pAniRes);

			AnimationAsset AniAsset;
			AniAsset.AddResource(refPath, pAniRes);
			AnimationAssetLoader loader;
			loader.Save(&AniAsset);

		}
	}
	//
	return pAsset;
}

SmartPointer<IWorldObj> FbxFileLoader::ProcessNode(FbxNode* pNode, string refPath, SmartPointer<IWorldObj> pParent, SmartPointer<SkeletonObj> pSkeletonObj)
{
	refPath = refPath + "/" + pNode->GetName() + ".mesh";
	FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();

	//
	SmartPointer<IWorldObj> pObj;// = SmartPointer<IWorldObj>(new IWorldObj);

	//

	
	if (pAttribute != nullptr)
	{
		switch (pAttribute->GetAttributeType())
		{
			case FbxNodeAttribute::EType::eMesh:
			{
				pObj = new IWorldObj;
				SmartPointer<MeshResource> pRes = ProcessMesh(pNode, refPath, pObj, pSkeletonObj.get());
			}
			break;
			case FbxNodeAttribute::EType::eSkeleton:
			{
				
				SkeletonObj* pSkel = new SkeletonObj;
				pObj = pSkel;
				FbxSkeleton* pskl = pNode->GetSkeleton();
				//std::cout << "skeleton type:" << pskl->GetSkeletonType() << std::endl;
				FbxNode* pSkeRootNode = GetSkeletonRoot(pNode);
				FbxSkeleton* pSklRoot = pSkeRootNode->GetSkeleton();
				if (pSkeRootNode == pNode)
				{
					pSkeletonObj = pSkel;
					pSkeletonObj->m_bIsRoot = true;
					pObj->m_strName = "SkeletonRoot";
				}
				if (pSkeletonObj->m_bIsRoot == true)
				{
					ProcessSkeleton(pSkeRootNode, m_fileDir + pNode->GetName() + ".skeleton.xml", pObj);
				}
			}
			default:
			break;
		}
	}
	//
	if (pObj == nullptr)
	{
		pObj = new IWorldObj;
	}
	pObj->m_strName = pNode->GetName();
	FbxTransform nodeTrans = pNode->GetTransform();
	FbxDouble3 trans = pNode->LclTranslation.Get();
	FbxDouble3 rot = pNode->LclRotation.Get();
	FbxDouble3 scal = pNode->LclScaling.Get();

	SmartPointer<Transform> pTransform = pObj->GetModule(0).SmartPointerCast<Transform>();
	pTransform->SetTranslate((float)trans.mData[0], (float)trans.mData[2], (float)trans.mData[1]);
	pTransform->SetScale((float)scal.mData[0], (float)scal.mData[2], (float)scal.mData[1]);
	pTransform->SetOrientation(AngleToRad((float)rot.mData[0]), AngleToRad((float)rot.mData[2]), AngleToRad((float)rot.mData[1]));
	//
	int nChild = pNode->GetChildCount();

	//
	bool processSkeletonParent = false;
	std::string SkeleonName = "";
	for (int i = 0; i < nChild; ++i)
	{
		FbxNode* pChildNode = pNode->GetChild(i);
		if (pChildNode->GetSkeleton() != nullptr)
		{
			SkeleonName = pChildNode->GetName();
		}
		SmartPointer<IWorldObj> pChild = ProcessNode(pChildNode, refPath, nullptr, pSkeletonObj);
		SkeletonObj* pSkel = dynamic_cast<SkeletonObj*>(pChild.get());
		if (pSkel != nullptr && pSkel->m_bIsRoot)
		{
 			processSkeletonParent = true;
			//SkeleonName = pChildNode->GetName();
		}
		pObj->addChild(pChild);
	}
	if (processSkeletonParent == true)
	{
		SkeletonModule* pSkeleton = pObj->addModule<SkeletonModule>().get();
		ProcessSkeletonRoot(pObj.get());
		//
		std::string refPath;// = m_fileDir + pNode->GetName() + ".skeleton.xml";
		refPath = strSkeletonPath + SkeleonName + ".skeleton.xml";
		pSkeleton->SetSkeletonRes(ResourceManager<SkeletonResource>::GetInstance()->GetResource(refPath).get());
		//
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
SmartPointer<MeshResource> FbxFileLoader::ProcessMesh(FbxNode* pNode, string refPath, SmartPointer<IWorldObj> obj, SmartPointer<IWorldObj> pSkeletonObj)
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
	refPath = strMeshPath + pNode->GetName() + ".mesh";
	//
	if (ResourceManager<MeshResource>::GetInstance()->GetResource(refPath) != nullptr)
	{
		refPath = strMeshPath + pNode->GetName() + "a" + ".mesh";
	}

	vecMeshList.push_back(pMesh);
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
	std::vector<float> areaVec;//Ãæ»ý
	std::vector<float> normalVec;
	std::vector<float> uvVec;
	std::vector<vector<stSkinInfo>> skinInfoVec;
	unsigned int nMaxBonePerVertex = 0;
	skinInfoVec.resize(cpCount);
	//get vertex pos
	for (unsigned int i = 0; i < cpCount; ++i)
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
			for (unsigned int i = 0; i < cpCount; ++i)
			{
				Vector3 normal;
				normal.m_fx = (float)pNormal->GetDirectArray().GetAt(i).mData[0];
				normal.m_fy = (float)pNormal->GetDirectArray().GetAt(i).mData[1];
				normal.m_fz = (float)pNormal->GetDirectArray().GetAt(i).mData[2];
				normalVec.push_back(normal.m_fx);
				normalVec.push_back(normal.m_fz);
				normalVec.push_back(normal.m_fy);

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
					np.y = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[2];
					np.z = (float)pNormal->GetDirectArray().GetAt(i * 3 + j).mData[1];
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
		std::cout << "texture uv0 cannot find" << std::endl;
	}
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
				uvVec[indexVec[i] * 2 + 1] = 1 - v;
			}
			//for each (float c in uvVec)
			//{
			//	std::cout << "uv:" << c << std::endl;
			//}
		}
	}

#pragma endregion
#pragma region AddSkinInfo
	bool bHasSkinInfo = false;
	int deformerCount = pMesh->GetDeformerCount();
	if (deformerCount == 1 && false)
	{
		bHasSkinInfo = true;
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
			SmartPointer<SkeletonResource> pSkeRes = nullptr;
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
#pragma region CalTangent
#pragma endregion
#pragma region AddMeshResource
	SmartPointer<Mesh> pMeshModule;
	pMeshModule = pModuleOwener->addModule<Mesh>();
	pMeshModule->SetMeshResource(pMeshResource);
	EnumIndexDesc eIndexDesc = EIndexInt;
	int nIndexLength = indexVec.size();
	if (nIndexLength <= 65535)
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
	desc.usedesc = EVertexUV;
	desc.typedesc = EVertexTypeFloat2;
	desc.nOffset = nVBOffset;
	pMeshResource->m_VertexData->vecDataDesc.push_back(desc);
	nVBOffset += sizeof(float) * 2;
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
		pMeshResource->m_VertexData->nBoneNum = nMaxBonePerVertex;
	}
	else
	{
		pMeshResource->m_VertexData->nBoneNum = 0;
	}



	pMeshResource->m_VertexData->nNumVertex = cpCount;
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
								*pChar = vecBlendIndex[i];
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
	SmartPointer<RasterMaterial> pMatRes = ProcessMaterial(pMat);
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
		string meshName = getFileNameWithoutSuffix(refPath);
		string subRefPath = strMeshPath + meshName + "_" + pMat->GetName() + ".mesh";
		SmartPointer<MeshResource> pSubMesh = ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>(subRefPath);// (new MeshResource);
		m_pAsset->AddResource(subRefPath, pSubMesh.get());
		SmartPointer<Mesh> pSubMeshModule = obj->addModule<Mesh>();
		pSubMeshModule->SetMeshResource(pSubMesh);
		bRemoveMainMesh = true;
		//
		SmartPointer<RasterMaterial> pMatRes = ProcessMaterial(pMat);
		m_pAsset->AddResource(pMatRes->GetRefPath(), pMatRes.get());
		pSubMeshModule->m_pSharedMaterial = pMatRes.get();
		//



		pSubMesh->m_VertexData->vecDataDesc = pMeshResource->m_VertexData->vecDataDesc;
		pSubMesh->m_VertexData->nNumVertex = mapIndex.size();
		//check skin info
		if (pMeshResource->m_VertexData->nBoneNum > 0)
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
			for (unsigned int i = 0; i < pSubMesh->m_VertexData->nNumVertex; ++i)
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
		}
		int nVertexDataLength = pSubMesh->m_VertexData->GetVertexDataLength();
		int nBuffLength = nVertexDataLength * pSubMesh->m_VertexData->nNumVertex;
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

			for (unsigned int i = 0; i < pSubMesh->m_VertexData->nNumVertex; ++i)
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

SmartPointer<IWorldObj> FbxFileLoader::ProcessSkeleton(FbxNode* pNode, string refPath, SmartPointer<IWorldObj> pObj /*= nullptr*/)
{
	FbxSkeleton* pSke = pNode->GetSkeleton();
	if (m_mapSkeleton.find(pSke) != std::end(m_mapSkeleton))
	{
		return nullptr;
	}
	refPath = strSkeletonPath + pNode->GetName() + ".skeleton.xml";
	SmartPointer<SkeletonResource> pSkeleton = ResourceManager<SkeletonResource>::GetInstance()->CreateResource<SkeletonResource>(refPath);
	Bone* pRoot = new Bone();
	pSkeleton->m_pRoot = pRoot;
	int BoneIndex = 0;
	ProcessBone(pSkeleton, pRoot, pNode, BoneIndex);
	m_pAsset->AddResource(refPath, pSkeleton.get());
	m_mapSkeleton[pSke] = pSkeleton;
	m_mapSkeObj[pSke] = pObj;
	pSkeleton->m_nBoneNum = pSkeleton->m_mapBone.size();
	return nullptr;

}

void FbxFileLoader::ProcessBone(SmartPointer<SkeletonResource> pRes, Bone* pBone, FbxNode* pObj, int& index)
{
	if (pBone == nullptr)
	{
		return;
	}
	m_SkeletonToFbxNode[pRes.get()].push_back(pObj);
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
	pBone->m_strName = pObj->GetName();
	//pObj->SetName(pBone->m_strName.c_str());
	pBone->nIndex = index;
	std::cout << "boneindex:" << index<<std::endl;
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

SmartPointer<RasterMaterial> FbxFileLoader::ProcessMaterial(FbxSurfaceMaterial* pMat)
{
	if (m_mapMaterial.find(pMat) != std::end(m_mapMaterial))
	{
		return m_mapMaterial[pMat].SmartPointerCast<RasterMaterial>();
	}
	FbxSurfacePhong* pSrfPhong = (FbxSurfacePhong*)pMat;
	int nProp = pMat->GetSrcPropertyCount();
	FbxProperty pProp = pSrfPhong->GetFirstProperty();


	SmartPointer<RasterMaterial> pMatRes = ResourceManager<MaterialResource>::GetInstance()->CreateResource<RasterMaterial>(strMaterialPath + pMat->GetName() + ".smat.xml");
	m_mapMaterial[pMat] = pMatRes.get();

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

			string strProperty = pProp.GetName();
			string fileName = getFileName(pTex->GetName());

			if (_tcsstr(strProperty.c_str(), "Diffuse") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(strTexturePath + fileName).get();
				if (_access((strTexturePath + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), strTexturePath + fileName);
				}

			}
			else if (_tcsstr(strProperty.c_str(), "Specular") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(strTexturePath + fileName).get();
				if (_access((strTexturePath + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), strTexturePath + fileName);
				}
			}
			else if (_tcsstr(strProperty.c_str(), "Normal") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(strTexturePath + fileName).get();
				if (_access((strTexturePath + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), strTexturePath + fileName);
				}
			}
			else if (_tcsstr(strProperty.c_str(), "Emissive") != nullptr)
			{
				TMatArg<TextureSampler>* matSampler = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
				matSampler->m_strName = strProperty;
				pMatRes->AddArg(strProperty, matSampler);
				matSampler->m_Data.m_pTexture = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(strTexturePath + fileName).get();
				if (_access((strTexturePath + fileName).c_str(), 0) == -1)
				{
					CpyFile(pTex->GetName(), strTexturePath + fileName);
				}
			}
		}
		MaterialPass* pPass = new MaterialPass();
		TMatArg<GameColor>* pArg = new TMatArg<GameColor>(EMATARGTYPECOLOR);
		pArg->m_Data = GameColor::white;
		//pMatRes->AddArg("MainColor", pArg);
		pMatRes->AddPass("First", pPass);
		AssetManager::GetInstance()->LoadAsset("./data/shader/VertexStandard.vsm");
		AssetManager::GetInstance()->LoadAsset("./data/shader/FragSpec.fsm");
		pPass->m_eVertexShaderType = EVERTEXSHADERORIGIN;
		pPass->m_eFragShaderType = EFRAGSHADERORIGIN;
		pPass->m_pVertexShader = ResourceManager<VertexShader>::GetInstance()->GetResource("./data/shader/VertexStandard.vsm");
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

void ZG::FbxFileLoader::ProcessSkeletonRoot(IWorldObj* pObj)
{
	int n = pObj->GetChildCount();
	std::vector<IWorldObj*> vecRemove;
	for (int i = 0; i < n; ++i)
	{
		IWorldObj* pChild = pObj->GetChild(i).get();
		if (dynamic_cast<SkeletonObj*>(pChild) != nullptr)
		{
			continue;
		}
		//
		std::vector<SmartPointer<Mesh>> vecMesh;
		pObj->GetAllModuleRecursive(vecMesh);

		int nMesh = vecMesh.size();
		for (int j = 0; j < nMesh; ++j)
		{
			Mesh* pMesh = pObj->addModule<Mesh>().get();
			pMesh->CopyFrom(vecMesh[j].get());

			vecMesh[j]->m_pOwnerObj->removeModule(vecMesh[j].get());
		}
		//
		vecRemove.push_back(pChild);
	}
	for each (IWorldObj* pWorldObj in vecRemove)
	{
		pObj->removeChild(pWorldObj);
	}
}
