#include "stdafx.h"
#include "SceneTreeView.h"
#include <iostream>

SceneTreeView::SceneTreeView()
{
	//connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(SceneTreeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
}


SceneTreeView::~SceneTreeView()
{
}

void SceneTreeView::SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre)
{
	std::cout << "sel change" << std::endl;
}
