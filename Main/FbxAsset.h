#pragma once
#include "IAsset.h"

namespace fbxsdk_2015_1
{
	class FbxScene;
}
namespace ZG
{

	class PrefabResource;
	class MAIN_API FbxAsset :
		public IAsset
	{
	public:
		FbxAsset();
		virtual ~FbxAsset();

		/*

		*Summary: release asset and associate resource

		*Parameters:

		*     bReleaseResource:if release associate resource


		*Return : void

		*/
		virtual void Release(bool bReleaseResource);
		//
		SmartPointer<PrefabResource> getPrefabResource() const;


		std::vector<SmartPointer<IResource>> GetAllResource() const;
	private:
		fbxsdk_2015_1::FbxScene*	m_pFbxScene;
		friend class FbxFileLoader;
		friend class FbxAppImporter;
	};

}