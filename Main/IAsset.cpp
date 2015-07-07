#include "stdafx.h"
#include "IAsset.h"


IAsset::IAsset()
{
}


IAsset::~IAsset()
{
}

void IAsset::Release(bool bReleaseResource)
{

}

void IAsset::RemoveResource(std::string refPath)
{
	m_ResourceMap.erase(refPath);
}
