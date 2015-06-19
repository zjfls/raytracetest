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

		virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
		virtual bool	Save(IAsset* pAsset);
	private:
		void PrefabProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem);
		void PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem);
		void PrefabProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem);
		void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem);
		XmlPrefabLoader();
		void ProcessWorldObjElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const;
		void ProcessTransformElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const;
		void ProcessMeshElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const;
		friend class AssetManager;
	};

}