#pragma once
#include "qtoolbar.h"
#include <map>
#include <string>
namespace ZG
{
	class CommonToolBar :public QToolBar
	{
		Q_OBJECT
	public:
		CommonToolBar(const QString &title, QWidget *parent);
		virtual ~CommonToolBar();
		private slots:
		void onActionTrigger(QAction* pAction);


	private:
		void createAction();


		QAction* m_pSelectAction;
		QAction* m_pMoveAction;
		QAction* m_pRotationAction;
		QAction* m_pScaleAction;

		std::map<std::string, QAction*> m_mapActions;
	};
}


