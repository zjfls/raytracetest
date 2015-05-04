#pragma once
//#include "tinyxml2.h"
class PrefabResource;
class Mesh;
class Transform;
class MaterialResource;
class MeshResource;
class SkeletonResource;
class Bone;
class RasterMaterial;
//class tinyxml2::XMLElement;
//class tinyxml2::XMLDocument;

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
};
class IWorldObj;
class MAIN_API FbxAppImporter :public Singleton<FbxAppImporter>
{
public:
	FbxAppImporter();
	virtual ~FbxAppImporter();



	void ImportFbxFile(string path);
private:
	void ImportPrefab(shared_ptr<PrefabResource> pPrefab,string path);
	void ImportMesh(shared_ptr<MeshResource> pMesh, string path);
	void ImportSkeleton(shared_ptr<SkeletonResource> pSkeRes,string path);
	void ImportMaterial(shared_ptr<RasterMaterial> pMatRes, string path);
	void SkeletonProcessBone(tinyxml2::XMLDocument& doc,Bone* pBone,tinyxml2::XMLElement* pElem);
	void PrefabProcessWorldObj(tinyxml2::XMLDocument& doc,shared_ptr<IWorldObj> pObj, tinyxml2::XMLElement* elem);
	void PrefabProcessMeshModule(tinyxml2::XMLDocument& doc,shared_ptr<Mesh> pMesh,tinyxml2::XMLElement* pElem);
	//void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, MaterialResource* pMat, tinyxml2::XMLElement* pElem);
	void PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, shared_ptr<Transform> pTrans, tinyxml2::XMLElement* pElem);
	void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, shared_ptr<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem);


	std::map<string, string> m_refNameMap;
};
extern template  class MAIN_API  Singleton<FbxAppImporter>;
