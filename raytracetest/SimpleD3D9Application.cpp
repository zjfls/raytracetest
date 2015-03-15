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
	bUseNormal = true;
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
		1024, 768, 0, 0, GetModuleHandle(0), 0);
	m_hwnd = window;
	ShowWindow(window, SW_SHOWDEFAULT);
	//MSG msg;
	//while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
	//
	//D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

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

	
	D3DCAPS9 caps;// = nullptr;
	m_pd3dDevice->GetDeviceCaps(&caps);
	std::cout <<"maxVertexConst:"<< caps.MaxVertexShaderConst << std::endl;

	
}

void SimpleD3D9Application::SetupScene()
{

	InitVB();
	SetupCamera();
	//SetupLight();
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



HRESULT SimpleD3D9Application::InitVB()
{
	LPD3DXBUFFER pCode;
	LPD3DXBUFFER pError;
	if (D3DXCompileShaderFromFile(".\\data\\shader\\vertex.hlsl", NULL, NULL, "vMain", "vs_3_0", D3DXSHADER_DEBUG, &pCode, &pError, &m_pVCT) != D3D_OK)
	{
		std::cout << "compile vertex shader failed" << std::endl;
		std::cout << (char*)pError->GetBufferPointer() << std::endl;
		return E_FAIL;
	}
	if (m_pd3dDevice->CreateVertexShader((DWORD*)pCode->GetBufferPointer(), &m_pVertexShader) != D3D_OK)
	{
		std::cout << "create vertex shader failed" << std::endl;
		return E_FAIL;
	}
	pCode->Release();
	pCode = 0;
	SAFE_RELEASE(pError);
	if (D3DXCompileShaderFromFile(".\\data\\shader\\frag.hlsl", NULL, NULL, "pMain", "ps_3_0", D3DXSHADER_DEBUG, &pCode, &pError, &m_pFCT) != D3D_OK)
	{
		std::cout << "compile pixel shader failed" << std::endl;
		std::cout << (char*)pError->GetBufferPointer() << std::endl;
		return E_FAIL;
	}
	if (m_pd3dDevice->CreatePixelShader((DWORD*)pCode->GetBufferPointer(), &m_pFragShader) != D3D_OK)
	{
		std::cout << "create pixel shader failed" << std::endl;
		return E_FAIL;
	}
	pCode->Release();
	pCode = 0;
	SAFE_RELEASE(pError);
	///////////////////////////////
	if (FAILED(D3DXCreateTextureFromFile(m_pd3dDevice, "return_portal_01.tga", &m_pDiffuseTexture)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(m_pd3dDevice, ".\\data\\meshes\\return_portal_01.tga", &m_pDiffuseTexture)))
		{
			MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	
	IAsset* pAsset = AssetManager::GetInstance()->LoadAsset("./data/meshes/file_split.fbx");//Env_MuSinportal,Env_MuSinportalreturn_portal_01_INST
	MeshResource* pMesh = (MeshResource*)pAsset->GetResource(pAsset->m_strPath + "/RootNode/target001").get();
	pMeshRes = pMesh;
	//read material

	//
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(pMesh->m_VertexData.nNumVertex * pMesh->m_VertexData.GetVertexDataLength(),
		0, 0,
		D3DPOOL_MANAGED, &m_pVB, NULL)))
	{
		return E_FAIL;
	}
	void* pVertexData;
	if (FAILED(m_pVB->Lock(0, pMesh->m_VertexData.GetVertexDataLength() * pMesh->m_VertexData.nNumVertex, &pVertexData, 0)))
	{
		return E_FAIL;
	}

	float* pf = (float*)pMesh->m_VertexData.pData;
	for (int i = 0; i < pMesh->m_VertexData.nNumVertex; ++i)
	{
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 0);
		//std::cout << "pos"<<i<<":" << *(float*)pVertexData << " ";
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 1);
		//std::cout << *(float*)pVertexData << " ";
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 2);
		//std::cout << *(float*)pVertexData << std::endl;
		pVertexData = (float*)pVertexData + 1;

		//
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 0 + pMesh->m_VertexData.nNumVertex * 3);
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 1 + pMesh->m_VertexData.nNumVertex * 3);
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 3 + 2 + pMesh->m_VertexData.nNumVertex * 3);
		pVertexData = (float*)pVertexData + 1;

		//
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 2 + 0 + pMesh->m_VertexData.nNumVertex * 6);
		//std::cout << "data u:" << *(float*)pVertexData;
		pVertexData = (float*)pVertexData + 1;
		*(float*)pVertexData = *((float*)pMesh->m_VertexData.pData + i * 2 + 1 + pMesh->m_VertexData.nNumVertex * 6);
		//std::cout << "data v:" << *(float*)pVertexData << std::endl;
		pVertexData = (float*)pVertexData + 1;
		

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
		//unsigned short* pIndex = (unsigned short*)pIndexData;
		//for (int i = 0; i < pMesh->m_IndexData.indexNum; ++i)
		//{
		//	std::cout << "index" << i << ":" << (short)*pIndex << std::endl;
		//	pIndex++;
		//}
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
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pDiffuseTexture);
	SAFE_RELEASE(m_pVertexDecl);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pVCT);
	SAFE_RELEASE(m_pFragShader);
	SAFE_RELEASE(m_pFCT);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}

void SimpleD3D9Application::SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	

	//UINT iTime = timeGetTime() % 1000;
	//FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	//D3DXMatrixRotationY(&matWorld, fAngle);
	//m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);



}

void SimpleD3D9Application::SetupLight()
{
	// Set up a material. The material here just has the diffuse and ambient
	// colors set to yellow. Note that only one material can be used at a time.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pd3dDevice->SetMaterial(&mtrl);

	// Set up a white, directional light, with an oscillating direction.
	// Note that many lights may be active at a time (but each one slows down
	// the rendering of our scene). However, here we are just using one. Also,
	// we need to set the D3DRS_LIGHTING renderstate to enable lighting
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Position.x = 0.0f;
	light.Position.y = 1000.0f;
	light.Position.z = 0.0f;
	vecDir = D3DXVECTOR3(0,
		-1.0f,
		1);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 10000.0f;
	m_pd3dDevice->SetLight(0, &light);
	m_pd3dDevice->LightEnable(0, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Finally, turn on some ambient light.
	m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

IDirect3DVertexDeclaration9* SimpleD3D9Application::GetDeclarationFromMesh(MeshResource* pMesh)
{
	std::vector<D3DVERTEXELEMENT9> vecVertElem;
	D3DVERTEXELEMENT9 elem = { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 };
	vecVertElem.push_back(elem);
	elem = { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 };
	vecVertElem.push_back(elem);
	elem = { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };
	vecVertElem.push_back(elem);
	elem = D3DDECL_END();
	vecVertElem.push_back(elem);
	m_pd3dDevice->CreateVertexDeclaration((D3DVERTEXELEMENT9*)(&vecVertElem[0]),&m_pVertexDecl);
	return m_pVertexDecl;
}

void SimpleD3D9Application::OnResetDevice()
{
	
	SetupCamera();
	//SetupLight();
	GetDeclarationFromMesh(pMeshRes);

}
void SimpleD3D9Application::Render()
{

	//
	if (m_pd3dDevice == nullptr)
	{
		return;
	}
	if (m_pVertexShader == nullptr)
	{
		return;
	}
	if (m_pFragShader == nullptr)
	{
		return;
	}
	//
	HRESULT hr = m_pd3dDevice->TestCooperativeLevel();
	switch (hr)
	{
		case D3DERR_DEVICELOST:
		{
			OnLostDevice();
			return;
		}
		break;
		case D3DERR_DEVICENOTRESET:
		{
			m_pd3dDevice->Reset(&d3dpp);
			OnResetDevice();
		}
		break;
		default:
		{

		}
		break;
	}
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	DWORD fTime = timeGetTime();
	D3DXMatrixRotationY(&matWorld, fTime / 500.0f);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);


	D3DXVECTOR3 vEyePt(0.0f, 320.0f, -400.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 100.0f, -50.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1024.0f / 768.0f, 1.0f, 2000.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	//D3DXMATRIXA16 matWorld = matWorld;
	D3DXMATRIXA16 matViewProj = matView * matProj;
	m_pVCT->SetMatrix(m_pd3dDevice, "mWorld", &matWorld);
	m_pVCT->SetMatrix(m_pd3dDevice, "mViewProj", &matViewProj);



	D3DXMATRIXA16 m_WorldInverse ;
	D3DXMatrixRotationY(&m_WorldInverse, fTime / -500.0f);
	D3DXVECTOR3 lightDir = { 0.0f, -1.0f, 1.0f};
	D3DXVec3Normalize(&lightDir, &lightDir);
	lightDir = -lightDir;
	D3DXVECTOR4 lightDir4;
	D3DXVec3Transform(&lightDir4, &lightDir, &m_WorldInverse);

	m_pFCT->SetVector(m_pd3dDevice, "lightDir", (D3DXVECTOR4*)&lightDir4);
	//m_pFCT->settex
	//

	// Clear the backbuffer to a blue color
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		m_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG);
		m_pd3dDevice->SetTexture(0, m_pDiffuseTexture);
		//SetupLight();
		m_pd3dDevice->SetVertexShader(m_pVertexShader);
		m_pd3dDevice->SetPixelShader(m_pFragShader);
		//m_pVCT->SetMatrix();
		m_pd3dDevice->SetVertexDeclaration(m_pVertexDecl);
		m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(float) * 8);
		m_pd3dDevice->SetIndices(m_pIB);
		//m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		//m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMeshRes->m_VertexData.nNumVertex, 0, pMeshRes->m_IndexData.indexNum / 3);
		//m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMeshRes->m_VertexData.nNumVertex, 0, 1);

		// End the scene
		m_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void SimpleD3D9Application::OnLostDevice()
{
	//std::cout << "lost device" << std::endl;
	if (m_pVertexDecl != nullptr)
	{
		m_pVertexDecl->Release();
		m_pVertexDecl = 0;
	}

}
