#pragma once
class FbxAppManager:public Singleton<FbxAppManager>
{
public:
	FbxAppManager();
	virtual ~FbxAppManager();


	bool Init();



	FbxManager* m_pFbxSdkManager;
	FbxScene*	m_pFbxScene;

};

