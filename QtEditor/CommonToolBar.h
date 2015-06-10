#pragma once
#include "qtoolbar.h"
namespace ZG
{
	class CommonToolBar :public QToolBar
	{
		Q_OBJECT
	public:
		CommonToolBar(const QString &title, QWidget *parent);
		virtual ~CommonToolBar();


	private:
		void createAction();


		QAction* m_pSelectAction;
		QAction* m_pMoveAction;
		QAction* m_pRotationAction;
		QAction* m_pScaleAction;
	};
}


