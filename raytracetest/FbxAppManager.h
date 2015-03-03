#pragma once
class FbxAppManager:public Singleton<FbxAppManager>
{
public:
	FbxAppManager();
	virtual ~FbxAppManager();


	bool Init();
	void testFbxLoad();


	//
	void ProcessNode(FbxNode* pNode);
	void ProcessMesh(FbxNode* pNode);
	FbxManager* m_pFbxSdkManager;
	FbxScene*	m_pFbxScene;

};

