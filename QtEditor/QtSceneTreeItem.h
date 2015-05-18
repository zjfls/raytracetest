#pragma once
class IWorldObj;
class QtSceneTreeItem :
	public QTreeWidgetItem
{
public:
	QtSceneTreeItem(int type = Type) :QTreeWidgetItem(type){};
	virtual ~QtSceneTreeItem();


	shared_ptr<IWorldObj> m_pObj;
};

