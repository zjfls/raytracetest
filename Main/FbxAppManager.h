#pragma once
#include "fbxsdk.h"
#include "Singleton.h"
class MAIN_API FbxAppManager :public Singleton<FbxAppManager>
{
public:
	FbxAppManager();
	virtual ~FbxAppManager();


	bool Init();



	FbxManager* m_pFbxSdkManager;
	FbxScene*	m_pFbxScene;

};

extern template class MAIN_API Singleton < FbxAppManager > ;