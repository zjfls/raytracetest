#include "stdafx.h"
#include "Texture.h"
#include "ResourceManager.h"
shared_ptr<ResourceManager<Texture>> Singleton<ResourceManager<Texture>>::_instance = nullptr;

Texture::Texture()
{
	eTexType = ETEXTYPEINVALID;
}


Texture::~Texture()
{
}
