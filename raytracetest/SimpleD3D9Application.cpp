#include "stdafx.h"
#include "SimpleD3D9Application.h"
#include "AssetManager.h"
#include "MeshResource.h"
#include "IAsset.h"
#include "d3dx9.h"
SimpleD3D9Application* Singleton<SimpleD3D9Application>::_instance = nullptr;
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z; // The transformed position for the vertex
	DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ)




SimpleD3D9Application::SimpleD3D9Application()
{
	m_pIB = nullptr;
}


SimpleD3D9Application::~SimpleD3D9Application()
{
}

void SimpleD3D9Application::OnInit()
{
	const char* const myclass = "myclass";
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
		0, 0, GetModuleHandle(0), LoadIcon(0, IDI_APPLICATION),
		LoadCursor(0, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
		0, myclass, LoadIcon(0, IDI_APPLICATION) };
	RegisterClassEx(&wndclass);
	HWND window = CreateWindowEx(0, myclass, "d3dwindow",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0);
	m_hwnd = window;
	ShowWindow(window, SW_SHOWDEFAULT);
	//MSG msg;
	//while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
	//
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		std::cout << "get d3d9 failed" << std::endl;
		return;
	}
		

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		std::cout << GetLastError() << std::endl;
		std::cout << "create device failed" << std::endl;
		system("pause");
		return;
	}

	
	

	
}

void SimpleD3D9Application::SetupScene()
{

	InitVB();
	SetupCamera();
	SetupLight();
}

void SimpleD3D9Application::OnEndInit()
{

}

void SimpleD3D9Application::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}
}

long SimpleD3D9Application::WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		std::cout << "\ndestroying window\n";
		SimpleD3D9Application::GetInstance()->CleanUp();
		PostQuitMessage(0);
		return 0L;
	case WM_LBUTTONDOWN:
		//std::cout << "\nmouse left button down at (" << LOWORD(lp)
		//	<< ',' << HIWORD(lp) << ")\n";
		// fall thru
	default:
		//std::cout << '.';
		return DefWindowProc(window, msg, wp, lp);
	}
}

void SimpleD3D9Application::Render()
{


	//
	if (m_pd3dDevice == nullptr)
	{
		return;
	}
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f),
		1.0f,
		sinf(timeGetTime() / 350.0f));
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;
	m_pd3dDevice->SetLight(0, &light);
	m_pd3dDevice->LightEnable(0, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matWorld, timeGetTime() / 500.0f);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//
	
	// Clear the backbuffer to a blue color
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		//m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
		//m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		m_pd3dDevice->SetVertexDeclaration(m_pVertexDecl);
		m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(float) * 6);
		m_pd3dDevice->SetIndices(m_pIB);
		//m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMeshRes->m_VertexData.nNumVertex, 0, pMeshRes->m_IndexData.indexNum / 3);

		// End the scene
		m_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT SimpleD3D9Application::InitVB()
{
	IAsset* pAsset = AssetManager::GetInstance()->LoadAsset("../meshes/plane.fbx");//Env_MuSinportal
	MeshResource* pMesh = (MeshResource*)pAsset->GetResource(pAsset->m_strPath + "/RootNode/Plane001").get();
	pMeshRes = pMesh;
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(pMesh->m_VertexData.nNumVertex * sizeof(float) * 6,
		0, 0,
		D3DPOOL_MANAGED, &m_pVB, NULL)))
	{
		return E_FAIL;
	}
	void* pVertexData;
	if (FAILED(m_pVB->Lock(0,sizeof(float) * 6 * pMesh->m_VertexData.nNumVertex,&pVertexData,0)))
	{
		return E_FAIL;
	}
	//memcpy(pVertexData, pMesh->m_VertexData.pData, sizeof(float) * 6 * pMesh->m_VertexData.nNumVertex);
	for (int i = 0; i < pMesh->m_VertexData.nNumVertex; ++i)
	{
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 0);
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 1);
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 2);
		pVertexData = (float*)pVertexData + 1;
		*((float*)pMesh->m_VertexData.pData + i * 3 + 0 + pMesh->m_VertexData.nNumVertex * sizeof(float) * 3);
		pVertexData = (float*)pVertexData + 1;
		*((float*)pMesh->m_VertexData.pData + i * 3 + 1 + pMesh->m_VertexData.nNumVertex * sizeof(float) * 3);
		pVertexData = (float*)pVertexData + 1;
		*((float*)pMesh->m_VertexData.pData + i * 3 + 2 + pMesh->m_VertexData.nNumVertex * sizeof(float) * 3);

	}
	m_pVB->Unlock();

	// Now we fill the vertex buffer. To do this, we need to Lock() the VB to
	// gain access to the vertices. This mechanism is required becuase vertex
	// buffers may be in device memory.
	//VOID* pVertices;
	//if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	//	return E_FAIL;
	//memcpy(pVertices, vertices, sizeof(vertices));
	//m_pVB->Unlock();


	//copy index data
	int sizeIndex = 2;
	D3DFORMAT indexFormat = D3DFMT_INDEX16;
	if (pMesh->m_IndexData.indexDesc == stIndexData::EIndexInt)
	{
		sizeIndex = 4;
		indexFormat = D3DFMT_INDEX32;
	}
	if (FAILED(m_pd3dDevice->CreateIndexBuffer(pMesh->m_IndexData.indexNum * sizeIndex, 0, indexFormat, D3DPOOL_MANAGED, &m_pIB, 0)))
	{
		return E_FAIL;
	}
	void* pIndexData;
	HRESULT hr = m_pIB->Lock(0, 0, &pIndexData, 0);
	if (SUCCEEDED(hr))
	{
		memcpy(pIndexData, pMesh->m_IndexData.pData, pMesh->m_IndexData.indexNum * sizeIndex);
	}
	m_pIB->Unlock();
	//
	GetDeclarationFromMesh(pMesh);

	//


	//
	return S_OK;
}

void SimpleD3D9Application::CleanUp()
{
	if (m_pVB != nullptr)
	{
		m_pVB->Release();
		m_pVB = nullptr;
	}
	if (m_pVB != nullptr)
	{
		m_pd3dDevice->Release();
		m_pd3dDevice = nullptr;
	}
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pd3dDevice = nullptr;
	}
}

void SimpleD3D9Application::SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	

	//UINT iTime = timeGetTime() % 1000;
	//FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	//D3DXMatrixRotationY(&matWorld, fAngle);
	//m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);


	D3DXVECTOR3 vEyePt(0.0f, 430.0f, -750.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void SimpleD3D9Application::SetupLight()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pd3dDevice->SetMaterial(&mtrl);
	// Finally, turn on some ambient light.
	m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);


	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(0,
		-0.5,
		1);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 10000.0f;
	m_pd3dDevice->SetLight(0, &light);
	m_pd3dDevice->LightEnable(0, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

IDirect3DVertexDeclaration9* SimpleD3D9Application::GetDeclarationFromMesh(MeshResource* pMesh)
{
	std::vector<D3DVERTEXELEMENT9> vecVertElem;
	D3DVERTEXELEMENT9 elem = { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 };
	vecVertElem.push_back(elem);
	elem = { 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, 0 };
	vecVertElem.push_back(elem);
	elem = D3DDECL_END();
	vecVertElem.push_back(elem);
	m_pd3dDevice->CreateVertexDeclaration((D3DVERTEXELEMENT9*)(&vecVertElem[0]),&m_pVertexDecl);
	return m_pVertexDecl;
}
