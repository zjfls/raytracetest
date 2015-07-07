#pragma once
#include "IAssetLoader.h"
namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
};
namespace ZG
{
	class IWorldObj;
	class Mesh;
	class Transform;
	class MaterialResource;
	class RasterMaterial;
	class MAIN_API XmlPrefabLoader :
		public IAssetLoader
	{
	public:

		~XmlPrefabLoader();

		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/);
		virtual bool	Save(IAsset* pAsset);
	public:
		static void LoadProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem);
		static void LoadProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem);
		static void LoadProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem);
		static void LoadProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem);
		static void LoadWorldObjElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj);
		static void LoadTransformElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj);
		static void LoadMeshElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj);
		friend class AssetManager;
	private:
		XmlPrefabLoader();
	};

}