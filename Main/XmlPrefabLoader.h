#pragma once
#include "IAssetLoader.h"
namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
};
class IWorldObj;
class MAIN_API XmlPrefabLoader :
	public IAssetLoader
{
public:
	
	~XmlPrefabLoader();

	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
private:
	XmlPrefabLoader();
	void ProcessWorldObjElem(tinyxml2::XMLElement* pElem,SmartPointer<IWorldObj> pObj) const;
	void ProcessTransformElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const;
	void ProcessMeshElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const;
	friend class AssetManager;
};

