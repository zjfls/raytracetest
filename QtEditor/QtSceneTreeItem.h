#pragma once
#include "IWorldObj.h"
#include <vector>
namespace ZG
{
	class IWorldObj;
	class QtSceneTreeItem :
		public QTreeWidgetItem
	{
	public:
		QtSceneTreeItem(int type = Type) :QTreeWidgetItem(type){};
		virtual ~QtSceneTreeItem();
		QtSceneTreeItem* GetItemByWorldObj(IWorldObj* pObj);
		//void	AddSceneTreeViewItem(QtSceneTreeItem* pParent, SmartPointer<IWorldObj> pObj);
		//void	GetAllItems(std::vector<QtSceneTreeItem*> vecItems);
		SmartPointer<ZG::IWorldObj> m_pObj;
	};

}


