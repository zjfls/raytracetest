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
	class RESOURCE_API Texture :
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

	RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<Texture> > ;
}