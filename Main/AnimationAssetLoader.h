#pragma once
#include "IAssetLoader.h"
namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}
namespace ZG
{
	template<class T>
	class AnimationCurve;
	struct stTransformData;
	class MAIN_API AnimationAssetLoader :public IAssetLoader
	{
	public:
		AnimationAssetLoader();
		virtual ~AnimationAssetLoader();

		IAsset* Load(string path, void* pArg /*= nullptr*/) override;
		void	Save(IAsset* pAsset) override;
	private:
		void	SaveTransformCurve(AnimationCurve<stTransformData>* pCurve, tinyxml2::XMLElement* pElem, tinyxml2::XMLDocument& doc);
	};

}

