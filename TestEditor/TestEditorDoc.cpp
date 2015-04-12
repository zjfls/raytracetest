
// TestEditorDoc.cpp : CTestEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TestEditor.h"
#endif

#include "TestEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestEditorDoc

IMPLEMENT_DYNCREATE(CTestEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestEditorDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CTestEditorDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CTestEditorDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTestEditorDoc, CDocument)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_ITestEditor ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {0E93D44A-D529-4AE0-B753-E02B115EFB3E}
static const IID IID_ITestEditor =
{ 0xE93D44A, 0xD529, 0x4AE0, { 0xB7, 0x53, 0xE0, 0x2B, 0x11, 0x5E, 0xFB, 0x3E } };

BEGIN_INTERFACE_MAP(CTestEditorDoc, CDocument)
	INTERFACE_PART(CTestEditorDoc, IID_ITestEditor, Dispatch)
END_INTERFACE_MAP()


// CTestEditorDoc ����/����

CTestEditorDoc::CTestEditorDoc()
{
	// TODO:  �ڴ����һ���Թ������

	EnableAutomation();

	AfxOleLockApp();
}

CTestEditorDoc::~CTestEditorDoc()
{
	AfxOleUnlockApp();
}

BOOL CTestEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTestEditorDoc ���л�

void CTestEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CTestEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CTestEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CTestEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTestEditorDoc ���

#ifdef _DEBUG
void CTestEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestEditorDoc ����
