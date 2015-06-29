#include "stdafx.h"
#include "QtSceneTreeItem.h"




QtSceneTreeItem::~QtSceneTreeItem()
{
}

QtSceneTreeItem* ZG::QtSceneTreeItem::GetItemByWorldObj(IWorldObj* pObj)
{
	if (pObj == m_pObj.get())
	{
		return this;
	}
	//
	int nChild = childCount();
	for (int i = 0; i < nChild; ++i)
	{
		QtSceneTreeItem* pItem = (QtSceneTreeItem*)child(i);
		QtSceneTreeItem* rt = pItem->GetItemByWorldObj(pObj);
		if (rt != nullptr)
		{
			return rt;
		}
	}
	return nullptr;
}




