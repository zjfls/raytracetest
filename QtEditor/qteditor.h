#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_qteditor.h"
#include "IListener.h"
class IWorldObj;
class QtSceneTreeItem;
class SceneTreeView;
class WorldObjPropertyBrowser;
class QtProperty;
class QtEditor : public QMainWindow,public IListener
{
	Q_OBJECT

public:
	QtEditor(QWidget *parent = 0);
	~QtEditor();
	virtual void OnNotify(std::string msg, std::shared_ptr<IListenerSubject> pSubject);
	//virtual void keyPressEvent(QKeyEvent * event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void childEvent(QChildEvent *event);
private slots:
	void	OnTimer();
	void	SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre);
	//void	valueChanged(QtProperty *pProp, const QVariant &variant);
	//
private:
	void	InitSceneTreeView();
	void	AddSceneTreeViewItem(QtSceneTreeItem* pParent,shared_ptr<IWorldObj> pObj);
	//
private:
	Ui::QtEditorClass ui;
	QTabWidget* m_pTabWidget;
	WorldObjPropertyBrowser* m_pTreePropertyBrowser;
public:
	SceneTreeView* m_pSceneTreeView;
};

#endif // QTEDITOR_H
