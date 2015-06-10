#pragma once
//#include "tinyxml2.h"


//class tinyxml2::XMLElement;
//class tinyxml2::XMLDocument;

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
};
namespace ZG
{
	class IWorldObj;
	class PrefabResource;
	class Mesh;
	class Transform;
	class MaterialResource;
	class MeshResource;
	class SkeletonResource;
	class Bone;
	class RasterMaterial;
	class MAIN_API FbxAppImporter :public Singleton<FbxAppImporter>, public GameObjectBase
	{
	public:
		FbxAppImporter();
		virtual ~FbxAppImporter();



		void ImportFbxFile(string path);
	private:
		void ImportPrefab(SmartPointer<PrefabResource> pPrefab, string path);
		void ImportMesh(SmartPointer<MeshResource> pMesh, string path);
		void ImportSkeleton(SmartPointer<SkeletonResource> pSkeRes, string path);
		void ImportMaterial(SmartPointer<RasterMaterial> pMatRes, string path);
		void SkeletonProcessBone(tinyxml2::XMLDocument& doc, Bone* pBone, tinyxml2::XMLElement* pElem);
		void PrefabProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem);
		void PrefabProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem);
		//void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, MaterialResource* pMat, tinyxml2::XMLElement* pElem);
		void PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem);
		void PrefabProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem);


		std::map<string, string> m_refNameMap;
	};
	extern template  class MAIN_API  Singleton < FbxAppImporter > ;
}