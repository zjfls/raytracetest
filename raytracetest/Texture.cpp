#include "stdafx.h"
#include "Texture.h"
#include "ResourceMananger.h"
ResourceManager<Texture>* Singleton<ResourceManager<Texture>>::_instance = nullptr;

Texture::Texture()
{
	eTexType = ETEXTYPEINVALID;
}


Texture::~Texture()
{
}
