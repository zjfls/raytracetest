// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WORLD_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WORLD_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef WORLD_EXPORTS
#define WORLD_API __declspec(dllexport)
#else
#define WORLD_API __declspec(dllimport)
#endif

// �����Ǵ� World.dll ������
class WORLD_API CWorld {
public:
	CWorld(void);
	
	// TODO:  �ڴ�������ķ�����
};

extern WORLD_API int nWorld;

WORLD_API int fnWorld(void);
