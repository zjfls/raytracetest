#pragma once
#include "IAsset.h"
namespace ZG
{
	class MAIN_API MeshAsset :
		public IAsset
	{
	public:
		MeshAsset();
		virtual ~MeshAsset();


		virtual void Release(bool bReleaseResource);
	};

}