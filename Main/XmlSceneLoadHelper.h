#pragma once
namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
};
namespace ZG
{
	class IWorldObj;
	class RasterMaterial;
	class Transform;
	class Mesh;
	class XmlSceneLoadHelper
	{
	public:
		XmlSceneLoadHelper();
		~XmlSceneLoadHelper();
		//load
		static void LoadProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem);
		static void LoadProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem);
		static void LoadProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem);
		static void LoadProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem);
		static void LoadWorldObjElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj);
		static void LoadTransformElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj);
		static void LoadMeshElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj);

		//save
		static void SaveProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem);
		static void SaveProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem);
		//void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, MaterialResource* pMat, tinyxml2::XMLElement* pElem);
		static void SaveProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem);
		static void SaveProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem);
		//
	};
}


