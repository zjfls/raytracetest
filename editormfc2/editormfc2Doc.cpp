
// editormfc2Doc.cpp : Ceditormfc2Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// 注意: 我们添加了对 IID_Ieditormfc2 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {0DC66F25-F66E-4FDE-9688-FD10C3F81F99}
static const IID IID_Ieditormfc2 =
{ 0xDC66F25, 0xF66E, 0x4FDE, { 0x96, 0x88, 0xFD, 0x10, 0xC3, 0xF8, 0x1F, 0x99 } };

BEGIN_INTERFACE_MAP(Ceditormfc2Doc, CDocument)
	INTERFACE_PART(Ceditormfc2Doc, IID_Ieditormfc2, Dispatch)
END_INTERFACE_MAP()


// Ceditormfc2Doc 构造/析构

Ceditormfc2Doc::Ceditormfc2Doc()
{
	// TODO:  在此添加一次性构造代码

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

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// Ceditormfc2Doc 序列化

void Ceditormfc2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void Ceditormfc2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void Ceditormfc2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// Ceditormfc2Doc 诊断

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


// Ceditormfc2Doc 命令
