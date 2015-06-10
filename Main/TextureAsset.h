#pragma once
#include "IAsset.h"
namespace ZG
{
	class TextureAsset :
		public IAsset
	{
	public:
		TextureAsset();
		virtual ~TextureAsset();
	};

}