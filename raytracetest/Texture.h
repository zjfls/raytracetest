#pragma once
#include "IResource.h"
#include "ResourceMananger.h"
enum ETEXTYPE
{
	ETEXTYPEINVALID,
	ETEXTYPE2D,
	ETEXTYPE3D,
};
class Texture :
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

