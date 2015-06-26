#pragma once
#include "IAsset.h"
namespace ZG
{
	class MAIN_API SingleResourceAsset :
		public IAsset
	{
	public:
		SingleResourceAsset();
		virtual ~SingleResourceAsset();
	};
}


