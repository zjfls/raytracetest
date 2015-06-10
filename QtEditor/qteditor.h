#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_qteditor.h"
#include "IListener.h"

class QtProperty;

namespace ZG
{
	class IWorldObj;
	
	class SceneTreeView;
	class WorldObjPropertyBrowser;
	class QListDataView;
	class CommonToolBar;
	class QtSceneTreeItem;

}

namespace ZG
{
	class QtEditor : public QMainWindow, public IListener
	{
		Q_OBJECT

	public:
		QtEditor(QWidget *parent = 0);
		~QtEditor();
		virtual void OnNotify(std::string msg, IListenerSubject* pSubject);
		//virtual void keyPressEvent(QKeyEvent * event);
		virtual bool eventFilter(QObject *obj, QEvent *event);
		virtual void childEvent(QChildEvent *event);
		private slots:
		void	OnTimer();
		void	SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre);
		//void	DataItemClicked(const QModelIndex &);
		//void	valueChanged(QtProperty *pProp, const QVariant &variant);
		//
	private:
		void	InitSceneTreeView();
		void	AddSceneTreeViewItem(QtSceneTreeItem* pParent, SmartPointer<IWorldObj> pObj);
		void	CreateToolBar();
		//
	private:
		Ui::QtEditorClass ui;
		QTabWidget* m_pTabWidget;
		WorldObjPropertyBrowser* m_pTreePropertyBrowser;


		//
		CommonToolBar* m_pCommonToolBar;
	public:
		SceneTreeView* m_pSceneTreeView;
		QListDataView* m_pDataView;
	};
}

#endif // QTEDITOR_H
