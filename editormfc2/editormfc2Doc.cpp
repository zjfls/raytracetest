
// editormfc2Doc.cpp : Ceditormfc2Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "editormfc2.h"
#endif

#include "editormfc2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ceditormfc2Doc

IMPLEMENT_DYNCREATE(Ceditormfc2Doc, CDocument)

BEGIN_MESSAGE_MAP(Ceditormfc2Doc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Ceditormfc2Doc, CDocument)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_Ieditormfc2 ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {0DC66F25-F66E-4FDE-9688-FD10C3F81F99}
static const IID IID_Ieditormfc2 =
{ 0xDC66F25, 0xF66E, 0x4FDE, { 0x96, 0x88, 0xFD, 0x10, 0xC3, 0xF8, 0x1F, 0x99 } };

BEGIN_INTERFACE_MAP(Ceditormfc2Doc, CDocument)
	INTERFACE_PART(Ceditormfc2Doc, IID_Ieditormfc2, Dispatch)
END_INTERFACE_MAP()


// Ceditormfc2Doc ����/����

Ceditormfc2Doc::Ceditormfc2Doc()
{
	// TODO:  �ڴ����һ���Թ������

	EnableAutomation();

	AfxOleLockApp();
}

Ceditormfc2Doc::~Ceditormfc2Doc()
{
	AfxOleUnlockApp();
}

BOOL Ceditormfc2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// Ceditormfc2Doc ���л�

void Ceditormfc2Doc::Serialize(CArchive& ar)
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
void Ceditormfc2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Ceditormfc2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void Ceditormfc2Doc::SetSearchContent(const CString& value)
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

// Ceditormfc2Doc ���

#ifdef _DEBUG
void Ceditormfc2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Ceditormfc2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ceditormfc2Doc ����
