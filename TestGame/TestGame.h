// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TESTGAME_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TESTGAME_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TESTGAME_EXPORTS
#define TESTGAME_API __declspec(dllexport)
#else
#define TESTGAME_API __declspec(dllimport)
#endif

// �����Ǵ� TestGame.dll ������
class TESTGAME_API CTestGame {
public:
	CTestGame(void);
	// TODO:  �ڴ�������ķ�����
};

extern TESTGAME_API int nTestGame;

TESTGAME_API int fnTestGame(void);
class ApplicationBase;
//
extern "C" TESTGAME_API ApplicationBase* CreateRenderSystem();