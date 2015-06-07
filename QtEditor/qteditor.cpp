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
#include "SceneTreeView.h"
#include "CommonToolBar.h"
#include "QListDataView.h"
#include <typeinfo>
#include <unordered_map>
#include <vector>
//#include "QtRenderView.h"
//struct test
//{
//	test(const type_info& i):info(i){};
//	const type_info& info;
//
//};
QtEditor::QtEditor(QWidget *parent)
	: QMainWindow(parent)
{
	//std::vector<test> test2;
	//test a(typeid(EditorApplication));
	//test2.push_back(a);
	//for each (test a in test2)
	//{
	//	if (a.info == typeid(EditorApplication))
	//	{
	//		std::cout << "find:" << "EditorApplication" << std::endl;
	//	}
	//}
	//kmap[typeid(EditorApplication)] = typeid(EditorApplication).name();
	m_pSceneTreeView = nullptr;
	QDockWidget *dock = new QDockWidget(tr("SceneTreeView"), this);
	m_pSceneTreeView = new SceneTreeView();
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


	//const type_info& info = typeid(EditorApplication);
	//std::cout << typeid(EditorApplication).name() << std::endl;
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
	m_pTreePropertyBrowser = new WorldObjPropertyBrowser();
	pPropertyDock->setWidget(m_pTreePropertyBrowser);
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
	//tool bar
	CreateToolBar();
	//新建定时器
	connect(m_pSceneTreeView, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(SceneTreeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));

	//关联定时器计满信号和相应的槽函数

	timer->start(1);


	QDockWidget* pDataDock = new QDockWidget(tr("Data"));
	QWidget*	pDataWidget = new QWidget(this);
	pDataDock->setWidget(pDataWidget);
	QHBoxLayout* layout = new QHBoxLayout(pDataDock);
	
	//
	m_pDataView = new QListDataView;
	QFileSystemModel *pFileModel = new QFileSystemModel;
	pFileModel->setReadOnly(false);
	pFileModel->setFilter(QDir::Files);
	m_pDataView->setModel(pFileModel);
	m_pDataView->setViewMode(QListView::IconMode);
	m_pDataView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	m_pDataView->setAlternatingRowColors(false);
	m_pDataView->viewport()->setAttribute(Qt::WA_StaticContents);
	m_pDataView->setAttribute(Qt::WA_MacShowFocusRect, false);
	pFileModel->setRootPath(QDir::currentPath());
	m_pDataView->setRootIndex(pFileModel->index(QDir::currentPath() + tr("/data/")));

	
	///
	QTreeView* pTreeView = new QTreeView;
	QFileSystemModel *pDirModel = new QFileSystemModel;
	pDirModel->setFilter(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
	pTreeView->setModel(pDirModel);
	pDirModel->setRootPath(QDir::currentPath());
	pTreeView->setRootIndex(pDirModel->index(QDir::currentPath() + tr("/data/")));
	pTreeView->setMinimumHeight(100);
	pTreeView->setMinimumWidth(50);
	pTreeView->setBaseSize(QSize(50, 100));

	//
	layout->addWidget(pTreeView);
	layout->addWidget(m_pDataView);
	layout->setStretchFactor(pTreeView, 2.0f);
	layout->setStretchFactor(m_pDataView, 10.0f);
	pDataWidget->setLayout(layout);
	tabifyDockWidget(ui.dockWidget_2, pDataDock);
	m_pDataView->m_pDirectoryView = pTreeView;
	connect(pTreeView, SIGNAL(doubleClicked(const QModelIndex &)), m_pDataView, SLOT(DirectoryDoubleClicked(const QModelIndex &)));
	
}

QtEditor::~QtEditor()
{

}

void QtEditor::OnNotify(std::string msg, IListenerSubject* pSubject)
{
	if (msg == "InitScene")
	{
		//pFrm->m_wndSceneTreeView.InitSceneTreeView();
		InitSceneTreeView();
		
	}
	if (msg == "SelectChange")
	{
		m_pTreePropertyBrowser->SetTarget(EditorApplication::GetInstance()->m_SelectObj);
		//pFrm->m_wndProperties.UpdateWorldObjProperty(EditorApplication::GetInstance()->m_SelectObj);
		
	}
}

void QtEditor::OnTimer()
{

	EditorApplication::GetInstance()->Run();
	//

	//
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
			//pRenderView->keyPressEvent(keyEvent);
			return false;
		}
		if (dynamic_cast<QTabWidget*>(obj) != nullptr)
		{
			//((QtRenderView*)dynamic_cast<QTabWidget*>(obj)->currentWidget())->keyPressEvent(keyEvent);
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
	m_pSceneTreeView->clear();
	SmartPointer<IWorldObj> pObj = EditorApplication::GetInstance()->m_pWorld->m_pRoot;
	QtSceneTreeItem *pRoot = new QtSceneTreeItem();
	m_pSceneTreeView->addTopLevelItem(pRoot);
	pRoot->setText(0, tr("SceneRoot"));
	pRoot->m_pObj = pObj;
	for (int i = 0; i < pObj->GetChildCount(); ++i)
	{
		AddSceneTreeViewItem(pRoot,pObj->GetChild(i));
	}

}

void QtEditor::AddSceneTreeViewItem(QtSceneTreeItem* pParent, SmartPointer<IWorldObj> pObj)
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



void QtEditor::SceneTreeItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPre)
{
	if (pCur == nullptr)
	{
		return;
	}
	QtSceneTreeItem* pSceneItem = (QtSceneTreeItem*)pCur;
	if (pSceneItem->m_pObj == nullptr)
	{
		return;
	}
	EditorApplication::GetInstance()->OnSelectChange(pSceneItem->m_pObj);
	//std::cout << "Name:" << pSceneItem->m_pObj->m_strName << std::endl;
}

void QtEditor::CreateToolBar()
{
	m_pCommonToolBar = new CommonToolBar(tr("CommonToolBar"), this);
	addToolBar(Qt::LeftToolBarArea, m_pCommonToolBar);
}

//void QtEditor::DataItemClicked(const QModelIndex &)
//{
//	std::cout << "data item clicked" << std::endl;
//}

//void QtEditor::valueChanged(QtProperty *pProp, const QVariant &variant)
//{
//
//}
