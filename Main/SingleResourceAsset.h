#pragma once
#include "IAsset.h"
namespace ZG
{
	class SingleResourceAsset :
		public IAsset
	{
	public:
		SingleResourceAsset();
		virtual ~SingleResourceAsset();
	};
}


