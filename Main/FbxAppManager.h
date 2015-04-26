#pragma once

#include "Singleton.h"
namespace fbxsdk_2015_1
{ 
	class FbxManager;
	class FbxScene;
};

class MAIN_API FbxAppManager :public Singleton<FbxAppManager>
{
public:
	FbxAppManager();
	virtual ~FbxAppManager();


	bool Init();



	fbxsdk_2015_1::FbxManager* m_pFbxSdkManager;
	fbxsdk_2015_1::FbxScene*	m_pFbxScene;

};

extern template class MAIN_API Singleton < FbxAppManager > ;