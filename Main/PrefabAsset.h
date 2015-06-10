#pragma once
#include "IAsset.h"
namespace ZG
{
	class MAIN_API PrefabAsset :
		public IAsset
	{
	public:
		PrefabAsset();
		virtual ~PrefabAsset();

		virtual void Release(bool bReleaseResource);

	};

}