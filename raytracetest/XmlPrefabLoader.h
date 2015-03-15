#pragma once
#include "IAssetLoader.h"
namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
};
class XmlPrefabLoader :
	public IAssetLoader
{
public:
	
	~XmlPrefabLoader();

	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
private:
	XmlPrefabLoader();
	void ProcessWorldObjElem(tinyxml2::XMLElement* pElem,IWorldObj* pObj) const;
	void ProcessTransformElem(tinyxml2::XMLElement* pElem, IWorldObj* pObj) const;
	void ProcessMeshElem(tinyxml2::XMLElement* pElem, IWorldObj* pObj) const;
	friend class AssetManager;
};

