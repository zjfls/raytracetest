#pragma once
#include "ApplicationBase.h"
#include "d3d9.h"
#include "d3dx9shader.h"

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
	void		CleanUp();
private:
	IDirect3DVertexDeclaration9* GetDeclarationFromMesh(MeshResource* pMesh);
	void Render();
	HRESULT InitVB();
	void SetupCamera();
	void SetupLight();
	void OnResetDevice();
	void OnLostDevice();
	static long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
private:
	LPDIRECT3D9             m_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       m_pd3dDevice; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9 m_pVB; // Buffer to hold vertices
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	LPDIRECT3DTEXTURE9		m_pDiffuseTexture;
	IDirect3DVertexDeclaration9*	m_pVertexDecl;
	HWND					m_hwnd;
	MeshResource*			pMeshRes;
	D3DPRESENT_PARAMETERS	d3dpp;
	LPDIRECT3DVERTEXSHADER9 m_pVertexShader;
	LPD3DXCONSTANTTABLE		m_pVCT;
	LPDIRECT3DPIXELSHADER9	m_pFragShader;
	LPD3DXCONSTANTTABLE		m_pFCT;
	bool bUseNormal;
};

