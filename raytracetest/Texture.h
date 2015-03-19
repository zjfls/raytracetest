#pragma once
#include "IResource.h"
#include "ResourceMananger.h"
class Texture :
	public IResource
{
	protected:
		Texture();
public:
	virtual ~Texture();
	friend class ResourceManager < Texture >;
};

