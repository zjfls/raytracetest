#pragma once
#include "Texture.h"
class RESOURCE_API Texture2D :
	public Texture
{
public:
	Texture2D();
	virtual ~Texture2D();


	friend class ResourceManager < Texture2D > ;
};
