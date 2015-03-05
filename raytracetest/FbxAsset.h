#pragma once
#include "IAsset.h"
class FbxAsset :
	public IAsset
{
public:
	FbxAsset();
	virtual ~FbxAsset();


	string m_strPath;
};

