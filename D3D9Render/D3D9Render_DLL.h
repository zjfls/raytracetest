// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� D3D9RENDER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// D3D9RENDER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
//#ifdef D3D9RENDER_EXPORTS
//#define D3D9RENDER_API __declspec(dllexport)
//#else
//#define D3D9RENDER_API __declspec(dllimport)
//#endif
//
//// �����Ǵ� D3D9Render.dll ������
//class D3D9RENDER_API CD3D9Render {
//public:
//	CD3D9Render(void);
//	// TODO:  �ڴ�������ķ�����
//};
//
//extern D3D9RENDER_API int nD3D9Render;
//
//D3D9RENDER_API int fnD3D9Render(void);
namespace ZG
{
	class RenderSystem;
}

extern "C" D3D9RENDER_API RenderSystem* CreateRenderSystem();
