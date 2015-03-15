#pragma once
//#include "tinyxml2.h"
class Prefab;
class Mesh;
class Transform;
class IMaterial;
class MeshResource;
//class tinyxml2::XMLElement;
//class tinyxml2::XMLDocument;

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
};
class FbxAppImporter:public Singleton<FbxAppImporter>
{
public:
	FbxAppImporter();
	virtual ~FbxAppImporter();



	void ImportFbxFile(string path);
private:
	void ImportPrefab(shared_ptr<Prefab> pPrefab,string path);
	void ImportMesh(shared_ptr<MeshResource> pMesh, string path);
	void PrefabProcessWorldObj(tinyxml2::XMLDocument& doc,IWorldObj* pObj, tinyxml2::XMLElement* elem);
	void PrefabProcessMeshModule(tinyxml2::XMLDocument& doc,Mesh* pMesh,tinyxml2::XMLElement* pElem);
	void PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, Transform* pTrans, tinyxml2::XMLElement* pElem);
	void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, IMaterial* pMaterial, tinyxml2::XMLElement* pElem);


	std::map<string, string> m_refNameMap;
};

