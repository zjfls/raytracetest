#pragma once
#include "IResource.h"
#include "ResourceManager.h"
namespace ZG
{
	enum ETEXTYPE
	{
		ETEXTYPEINVALID,
		ETEXTYPE2D,
		ETEXTYPECUBE,
	};
	class MAIN_API Texture :
		public IResource
	{
	protected:
		Texture();
	public:
		virtual ~Texture();
		friend class ResourceManager < Texture > ;
		ETEXTYPE GetTexType() const{ return eTexType; };
	protected:
		ETEXTYPE eTexType;
	};

	extern template class MAIN_API  Singleton < ResourceManager<Texture> >;
}