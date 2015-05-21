#pragma once
#include "QTreeWidget"
class SceneTreeView:public QTreeWidget
{
	Q_OBJECT
public:
	SceneTreeView();
	virtual ~SceneTreeView();
	private slots:
	void SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre);
};

