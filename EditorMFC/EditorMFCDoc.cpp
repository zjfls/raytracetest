
// EditorMFCDoc.cpp : CEditorMFCDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "EditorMFC.h"
#endif

#include "EditorMFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEditorMFCDoc

IMPLEMENT_DYNCREATE(CEditorMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CEditorMFCDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEditorMFCDoc, CDocument)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IEditorMFC ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {77B0D67A-7654-4297-A64C-B2D5AAA31853}
static const IID IID_IEditorMFC =
{ 0x77B0D67A, 0x7654, 0x4297, { 0xA6, 0x4C, 0xB2, 0xD5, 0xAA, 0xA3, 0x18, 0x53 } };

BEGIN_INTERFACE_MAP(CEditorMFCDoc, CDocument)
	INTERFACE_PART(CEditorMFCDoc, IID_IEditorMFC, Dispatch)
END_INTERFACE_MAP()


// CEditorMFCDoc ����/����

CEditorMFCDoc::CEditorMFCDoc()
{
	// TODO:  �ڴ����һ���Թ������

	EnableAutomation();

	AfxOleLockApp();
}

CEditorMFCDoc::~CEditorMFCDoc()
{
	AfxOleUnlockApp();
}

BOOL CEditorMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CEditorMFCDoc ���л�

void CEditorMFCDoc::Serialize(CArchive& ar)
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
void CEditorMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CEditorMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CEditorMFCDoc::SetSearchContent(const CString& value)
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

// CEditorMFCDoc ���

#ifdef _DEBUG
void CEditorMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEditorMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEditorMFCDoc ����
