#pragma once
#include "QTreeWidget"
namespace ZG
{
	class SceneTreeView :public QTreeWidget
	{
		Q_OBJECT
	public:
		SceneTreeView();
		virtual ~SceneTreeView();
		private slots:
		void SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre);
	};
}


