
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree ����
namespace ZG
{
	class CViewTree : public CTreeCtrl
	{
		// ����
	public:
		CViewTree();

		// ��д
	protected:
		virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

		// ʵ��
	public:
		virtual ~CViewTree();

	protected:
		DECLARE_MESSAGE_MAP()
	};
}

