// D3D9Render.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"
//#include "stdafx.h"
//#include "D3D9Render_DLL.h"
#include "D3D9RenderSystem.h"
//
//// ���ǵ���������һ��ʾ��
//D3D9RENDER_API int nD3D9Render=0;
//
//// ���ǵ���������һ��ʾ����
//D3D9RENDER_API int fnD3D9Render(void)
//{
//	return 42;
//}
class RenderSystem;
extern "C" D3D9RENDER_API RenderSystem* CreateRenderSystem()
{
	return new D3D9RenderSystem();
}

//// �����ѵ�����Ĺ��캯����
//// �й��ඨ�����Ϣ������� D3D9Render.h
//CD3D9Render::CD3D9Render()
//{
//	return;
//}
