// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� EDITOR_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// EDITOR_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
//#ifdef EDITOR_EXPORTS
//#define EDITOR_API __declspec(dllexport)
//#else
//#define EDITOR_API __declspec(dllimport)
//#endif
//
//// �����Ǵ� Editor.dll ������
//class EDITOR_API CEditor {
//public:
//	CEditor(void);
//	// TODO:  �ڴ�������ķ�����
//};
//
//extern EDITOR_API int nEditor;
//
//EDITOR_API int fnEditor(void);
