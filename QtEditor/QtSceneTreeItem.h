#pragma once
#include "IWorldObj.h"
namespace ZG
{
	class IWorldObj;
	class QtSceneTreeItem :
		public QTreeWidgetItem
	{
	public:
		QtSceneTreeItem(int type = Type) :QTreeWidgetItem(type){};
		virtual ~QtSceneTreeItem();


		SmartPointer<ZG::IWorldObj> m_pObj;
	};

}


