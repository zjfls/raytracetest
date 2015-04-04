#include "stdafx.h"
#include "testmeshresource.h"
#include "ResourceManager.h"
#include "MeshResource.h"

testmeshresource::testmeshresource()
{
	ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>("fsd");
}


testmeshresource::~testmeshresource()
{
}
