#pragma once
#include "IAssetLoader.h"
namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}
namespace ZG
{
	class Bone;
	class SkeletonXmlLoader :
		public IAssetLoader
	{
	public:
		SkeletonXmlLoader();
		virtual ~SkeletonXmlLoader();

		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/);
		virtual bool	Save(IAsset* pAsset);

	private:
		void SkeletonProcessBone(tinyxml2::XMLDocument& doc, Bone* pBone, tinyxml2::XMLElement* pElem);
	};

}

