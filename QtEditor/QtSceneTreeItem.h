#pragma once
class IWorldObj;
class QtSceneTreeItem :
	public QTreeWidgetItem
{
public:
	QtSceneTreeItem(int type = Type) :QTreeWidgetItem(type){};
	virtual ~QtSceneTreeItem();


	SmartPointer<IWorldObj> m_pObj;
};

