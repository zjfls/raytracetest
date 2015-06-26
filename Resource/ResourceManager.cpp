#include "stdafx.h"
#include "ResourceManager.h"
#include "SceneResource.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "Texture.h"
//
#include "PrefabResource.h"
#include "MeshResource.h"
#include "MaterialResource.h"


void ZG::ResourceManagerBase::ReleaseResource(IResource* pResource)
{
	if (dynamic_cast<SceneResource*>(pResource) != nullptr)
	{
		ResourceManager<SceneResource>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

	if (dynamic_cast<VertexShader*>(pResource) != nullptr)
	{
		ResourceManager<VertexShader>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

	if (dynamic_cast<FragShader*>(pResource) != nullptr)
	{
		ResourceManager<FragShader>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

	if (dynamic_cast<Texture*>(pResource) != nullptr)
	{
		ResourceManager<Texture>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

	if (dynamic_cast<MeshResource*>(pResource) != nullptr)
	{
		ResourceManager<MeshResource>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

	if (dynamic_cast<PrefabResource*>(pResource) != nullptr)
	{
		ResourceManager<PrefabResource>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

	if (dynamic_cast<MaterialResource*>(pResource) != nullptr)
	{
		ResourceManager<MaterialResource>::GetInstance()->RemoveResource(pResource->GetRefPath());
	}

}

IResource* ZG::ResourceManagerBase::LoadResource(std::string refPath)
{
	return nullptr;
}
