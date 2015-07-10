#pragma once
#include "QTreeWidget"
#include <vector>
namespace ZG
{
	class AddSceneGraphEventArg;
	class DeleteSceneGraphEventArg;
	class SceneGraphSelChangeArg;
	class QtSceneTreeItem;
	class IWorldObj;
	class SceneTreeView :public QTreeWidget
	{
		Q_OBJECT
	public:
		SceneTreeView();
		virtual ~SceneTreeView();


		void OnAddToScene(AddSceneGraphEventArg& arg);
		void OnDeleteFromScene(DeleteSceneGraphEventArg& arg);
		void OnSceneGraphSelChange(SceneGraphSelChangeArg& arg);
		QtSceneTreeItem* GetItemByWorldObj(IWorldObj* pObj);
		void	AddSceneTreeViewItem(QtSceneTreeItem* pParent, SmartPointer<IWorldObj> pObj);
		

	private:
		void	GetAllItem(std::vector<QtSceneTreeItem*>& vecItems);
		void	GetAllChildren(QtSceneTreeItem* pItem,std::vector<QtSceneTreeItem*>& vecItems, bool bRecursive = false);
		void	GetParentTree(std::vector<QtSceneTreeItem*>& vecParents,QtSceneTreeItem* pItem);
		private slots:
		void SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre);
		void	OnItemDoubleClicked(QTreeWidgetItem *item, int column);
		void	OnItemClicked(QTreeWidgetItem *item, int column);
		//void	OnSelectionChanged();
	};
}


