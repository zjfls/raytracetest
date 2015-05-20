#include "stdafx.h"
#include "qteditor.h"
#include "EditorApplication.h"
#include "QtRenderView.h"
#include "QtSceneTreeItem.h"
#include "IWorldObj.h"
#include "IWorld.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtpropertymanager.h"
#include "WorldObjPropertyBrowser.h"
//#include "QtRenderView.h"

QtEditor::QtEditor(QWidget *parent)
	: QMainWindow(parent)
{
	m_pSceneTreeView = nullptr;
	QDockWidget *dock = new QDockWidget(tr("SceneTreeView"), this);
	m_pSceneTreeView = new QTreeWidget();
	dock->setWidget(m_pSceneTreeView);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	//
	//
	ui.setupUi(this);
	//
	//EditorApplication::GetInstance()->Init(nullptr,nullptr);
	EditorApplication::GetInstance()->SetWindowID(winId());
	EditorApplication::GetInstance()->m_pEditorApp = this;
	EditorApplication::GetInstance()->Init(0, nullptr);
	//
	QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	QMainWindow::setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
	//setCorner(Qt:TopRightCorner, Qt::LeftDockWidgetArea);

	dock = new QDockWidget(tr("Customers"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QListWidget* customerList = new QListWidget(dock);
	customerList->addItems(QStringList()
		<< "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
		<< "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
		<< "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
		<< "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
		<< "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
		<< "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
	dock->setWidget(customerList);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	//viewMenu->addAction(dock->toggleViewAction());
	//dock->
	QDockWidget* doc1 = dock;
	dock = new QDockWidget(tr("Paragraphs"), this);
	QListWidget* paragraphsList = new QListWidget(dock);
	paragraphsList->addItems(QStringList()
		<< "Thank you for your payment which we have received today."
		<< "Your order has been dispatched and should be with you "
		"within 28 days."
		<< "We have dispatched those items that were in stock. The "
		"rest of your order will be dispatched once all the "
		"remaining items have arrived at our warehouse. No "
		"additional shipping charges will be made."
		<< "You made a small overpayment (less than $5) which we "
		"will keep on account for you, or return at your request."
		<< "You made a small underpayment (less than $1), but we have "
		"sent your order anyway. We'll add this underpayment to "
		"your next bill."
		<< "Unfortunately you did not send enough money. Please remit "
		"an additional $. Your order will be dispatched as soon as "
		"the complete amount has been received."
		<< "You made an overpayment (more than $5). Do you wish to "
		"buy more items, or should we return the excess to you?");
	dock->setWidget(paragraphsList);
	//addDockWidget(Qt::RightDockWidgetArea, dock);
	//doc1->tabf
	tabifyDockWidget(doc1, dock);
	//viewMenu->addAction(dock->toggleViewAction());

	connect(customerList, SIGNAL(currentTextChanged(QString)),
		this, SLOT(insertCustomer(QString)));
	connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
		this, SLOT(addParagraph(QString)));
	//
	QDockWidget* pPropertyDock = new QDockWidget(tr("Property"));
	WorldObjPropertyBrowser* pTreePropertyBrowser = new WorldObjPropertyBrowser();
	pPropertyDock->setWidget(pTreePropertyBrowser);
	tabifyDockWidget(doc1, pPropertyDock);


	QtRenderView* pRender = new QtRenderView();
	
	//setCentralWidget(pRender);
	//ui.tabWidget->addTab(pRender, tr("Scene"));
	m_pTabWidget = new QTabWidget;
	m_pTabWidget->addTab(pRender, tr("Scene"));
	m_pTabWidget->installEventFilter(this);
	setCentralWidget(m_pTabWidget);
	pRender->installEventFilter(this);

	QtRenderView* pRender2 = new QtRenderView();
	pRender2->installEventFilter(this);
	m_pTabWidget->addTab(pRender2, tr("Scene_2"));
	QTimer *timer = new QTimer(this); 

	//新建定时器

	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));

	//关联定时器计满信号和相应的槽函数

	timer->start(1);
}

QtEditor::~QtEditor()
{

}

void QtEditor::OnNotify(std::string msg, std::shared_ptr<IListenerSubject> pSubject)
{
	if (msg == "InitScene")
	{
		//pFrm->m_wndSceneTreeView.InitSceneTreeView();
		InitSceneTreeView();
		
	}
	if (msg == "SelectChange")
	{
		//pFrm->m_wndProperties.UpdateWorldObjProperty(EditorApplication::GetInstance()->m_SelectObj);
	}
}

void QtEditor::OnTimer()
{
	EditorApplication::GetInstance()->Run();
}

//void QtEditor::keyPressEvent(QKeyEvent * event)
//{
//	std::cout << "key pressed!" << std::endl;
//}

bool QtEditor::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {
		//and here put your own logic!!
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		QtRenderView* pRenderView = dynamic_cast<QtRenderView*>(obj);
		if (pRenderView != nullptr)
		{
			pRenderView->keyPressEvent(keyEvent);
			return false;
		}
		if (dynamic_cast<QTabWidget*>(obj) != nullptr)
		{
			((QtRenderView*)dynamic_cast<QTabWidget*>(obj)->currentWidget())->keyPressEvent(keyEvent);
			return false;
		}
		//qDebug("Ate key press %d", keyEvent->key());
		return false;
	}
	else {
		// standard event processing
		return QObject::eventFilter(obj, event);
	}
}

void QtEditor::childEvent(QChildEvent *event)
{
	if (event->added()) {
		event->child()->installEventFilter(this);
	}
}

void QtEditor::InitSceneTreeView()
{
	shared_ptr<IWorldObj> pObj = EditorApplication::GetInstance()->m_pWorld->m_pRoot;
	QtSceneTreeItem *pRoot = new QtSceneTreeItem();
	m_pSceneTreeView->addTopLevelItem(pRoot);
	pRoot->setText(0, tr("SceneRoot"));
	pRoot->m_pObj = pObj;
	for (int i = 0; i < pObj->GetChildCount(); ++i)
	{
		AddSceneTreeViewItem(pRoot,pObj->GetChild(i));
	}

}

void QtEditor::AddSceneTreeViewItem(QtSceneTreeItem* pParent, shared_ptr<IWorldObj> pObj)
{
	QtSceneTreeItem* pItem = new QtSceneTreeItem();
	pParent->addChild(pItem);
	pItem->setText(0, QString::fromStdString(pObj->m_strName));
	for (int i = 0; i < pObj->GetChildCount(); ++i)
	{
		AddSceneTreeViewItem(pItem, pObj->GetChild(i));
	}
}
