#pragma once
#include "ApplicationBase.h"
#include "d3d9.h"

class MeshResource;
class SimpleD3D9Application :
	public ApplicationBase,public Singleton<SimpleD3D9Application>
{
public:
	SimpleD3D9Application();
	virtual ~SimpleD3D9Application();
	

	virtual void OnInit();
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual void Run();
	IDirect3DVertexDeclaration9* GetDeclarationFromMesh(MeshResource* pMesh);

	void		CleanUp();
private:
	void Render();
	HRESULT InitVB();
	void SetupCamera();
	void SetupLight();
	static long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
private:
	LPDIRECT3D9             m_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       m_pd3dDevice; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9 m_pVB; // Buffer to hold vertices
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	IDirect3DVertexDeclaration9*	m_pVertexDecl;
	HWND					m_hwnd;
	MeshResource* pMeshRes;
	bool bUseNormal;
};

