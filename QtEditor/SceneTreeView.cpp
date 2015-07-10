#include "stdafx.h"
#include "SceneTreeView.h"
#include "EditorEvents.h"
#include <iostream>
#include "QtSceneTreeItem.h"
#include "EditorApplication.h"
#include "EditorSceneView.h"
#include "InputManager.h"
#include "InputInterface.h"

SceneTreeView::SceneTreeView()
{
	setSelectionMode(QAbstractItemView::NoSelection);
	//connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(SceneTreeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnItemDoubleClicked(QTreeWidgetItem*, int)));
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnItemClicked(QTreeWidgetItem*, int)));
	//connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(OnSelectionChanged()));
}


SceneTreeView::~SceneTreeView()
{
}

void SceneTreeView::SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre)
{
	std::cout << "sel change" << std::endl;
}

void ZG::SceneTreeView::OnAddToScene(AddSceneGraphEventArg& arg)
{
	//std::cout << "add item" << std::endl;
	QtSceneTreeItem* pParentItem = GetItemByWorldObj(arg.m_pParent);
	if (pParentItem != nullptr)
	{
		AddSceneTreeViewItem(pParentItem, arg.m_pObj);
		//
		QtSceneTreeItem* pSel = pParentItem->GetItemByWorldObj(arg.m_pObj);
		if (pSel != nullptr)
		{
			//EditorApplication::GetInstance()->SelectChange(pSel->m_pObj);
		}
		//
	}

}

void ZG::SceneTreeView::OnDeleteFromScene(DeleteSceneGraphEventArg& arg)
{
	//std::cout << "delte item" << std::endl;
	QtSceneTreeItem* pParentItem = GetItemByWorldObj(arg.m_pParent);
	QtSceneTreeItem* pChildItem = GetItemByWorldObj(arg.m_pObj);
	if (pParentItem != nullptr && pChildItem != nullptr)
	{
		pParentItem->removeChild(pChildItem);
	}
}

QtSceneTreeItem* ZG::SceneTreeView::GetItemByWorldObj(IWorldObj* pObj)
{
	int nTopLevelItem = topLevelItemCount();
	for (int i = 0; i < nTopLevelItem; ++i)
	{
		QtSceneTreeItem* pTreeItem = (QtSceneTreeItem*)topLevelItem(i);
		if (pTreeItem == nullptr)
		{
			return nullptr;
		}
		QtSceneTreeItem* rt = pTreeItem->GetItemByWorldObj(pObj);
		if (rt != nullptr)
		{
			return rt;
		}
	}
	return nullptr;
}

void ZG::SceneTreeView::AddSceneTreeViewItem(QtSceneTreeItem* pParent, SmartPointer<IWorldObj> pObj)
{
	QtSceneTreeItem* pItem = new QtSceneTreeItem();
	pParent->addChild(pItem);
	pItem->setText(0, QString::fromStdString(pObj->m_strName));
	pItem->m_pObj = pObj;
	for (int i = 0; i < pObj->GetChildCount(); ++i)
	{
		AddSceneTreeViewItem(pItem, pObj->GetChild(i));
	}
}

void ZG::SceneTreeView::OnSceneGraphSelChange(SceneGraphSelChangeArg& arg)
{
	std::vector<QtSceneTreeItem*> vecItems;
	GetAllItem(vecItems);
	for each (QtSceneTreeItem* pItem in vecItems)
	{
		pItem->setSelected(false);
	}

	for each (IWorldObj* pObj in arg.m_vecObjs)
	{


		QtSceneTreeItem* pItem = GetItemByWorldObj(pObj);

		if (pItem != nullptr)
		{
			std::vector<QtSceneTreeItem*> vecParents;
			GetParentTree(vecParents, pItem);
			for each (QtSceneTreeItem* pItem in vecParents)
			{
				pItem->setExpanded(true);
			}
			pItem->setSelected(true);
			pItem->setExpanded(true);
		}
	}



}

void ZG::SceneTreeView::GetAllItem(std::vector<QtSceneTreeItem*>& vecItems)
{
	int nTopLevelItem = topLevelItemCount();
	for (int i = 0; i < nTopLevelItem; ++i)
	{
		QtSceneTreeItem* pTreeItem = (QtSceneTreeItem*)topLevelItem(i);
		vecItems.push_back(pTreeItem);
		GetAllChildren(pTreeItem, vecItems, true);

	}
}

void ZG::SceneTreeView::GetAllChildren(QtSceneTreeItem* pItem, std::vector<QtSceneTreeItem*>& vecItems, bool bRecursive /*= false*/)
{
	int nChild = pItem->childCount();
	for (int i = 0; i < nChild; ++i)
	{
		QtSceneTreeItem* pChild = (QtSceneTreeItem*)pItem->child(i);
		vecItems.push_back(pChild);
		if (bRecursive == true)
		{
			GetAllChildren(pChild, vecItems, true);
		}
	}
}

void ZG::SceneTreeView::GetParentTree(std::vector<QtSceneTreeItem*>& vecParents, QtSceneTreeItem* pItem)
{
	if (pItem != nullptr && pItem->parent() != nullptr)
	{
		vecParents.push_back((QtSceneTreeItem*)pItem->parent());
		GetParentTree(vecParents, (QtSceneTreeItem*)pItem->parent());
	}

}

void ZG::SceneTreeView::OnItemDoubleClicked(QTreeWidgetItem *item, int column)
{
	QtSceneTreeItem* pItem = dynamic_cast<QtSceneTreeItem*>(item);
	if (pItem != nullptr)
	{
		EditorSceneView* pView = EditorApplication::GetInstance()->getActiveScene();
		if (pView != nullptr)
		{
			pView->FocusTarget(pItem->m_pObj.get());
		}
	}
}

void ZG::SceneTreeView::OnItemClicked(QTreeWidgetItem *item, int column)
{
	QtSceneTreeItem* pItem = dynamic_cast<QtSceneTreeItem*>(item);
	if (pItem->isSelected() == true)
	{
		EditorApplication::GetInstance()->RemoveSelection(pItem->m_pObj.get());
		return;
	}
	if (InputManager::GetInstance()->m_pIO->IsKeyDown(InputInterface::KeyCode::EKEYCTRL))
	{
		EditorApplication::GetInstance()->AddSelection(pItem->m_pObj.get());
	}
	else
	{
		EditorApplication::GetInstance()->SelectChange(pItem->m_pObj);
	}
}

//void ZG::SceneTreeView::OnSelectionChanged()
//{
//	std::cout << "selection Changed" << std::endl;
//}
