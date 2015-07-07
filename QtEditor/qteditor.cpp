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
#include "EditorCommandManager.h"
#include "EditorCommands.h"
#include <deque>
#include "EditorEvents.h"
#include "EditorSceneView.h"
#include "fileoperation.h"
#include "AssetManager.h"
#include "AnimationResource.h"
#include "IAsset.h"
#include "SingleResourceAsset.h"
#include "FilePath.h"
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
	EditorApplication* pInstance = EditorApplication::GetInstance();
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
	pInstance->getEvent<AddSceneGraphEventArg>("ADDTOSCENEGGRAPH")->addEventHandler(pInstance, std::bind(&SceneTreeView::OnAddToScene, m_pSceneTreeView, std::placeholders::_1));
	pInstance->getEvent<DeleteSceneGraphEventArg>("DELETEFROMSCENEGRAPH")->addEventHandler(pInstance, std::bind(&SceneTreeView::OnDeleteFromScene, m_pSceneTreeView, std::placeholders::_1));
	pInstance->getEvent<SceneGraphSelChangeArg>("SCENEGRAPHSELCHANGE")->addEventHandler(pInstance, std::bind(&SceneTreeView::OnSceneGraphSelChange, m_pSceneTreeView, std::placeholders::_1));
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
	pInstance->getEvent<EditorUpdateArg>("EDITORUPDATE")->addEventHandler(this, std::bind(&QtEditor::OnEditorUpdate, this, std::placeholders::_1));

	QtRenderView* pRender = new QtRenderView();
	pRender->m_strName = "Scene1";
	
	//setCentralWidget(pRender);
	//ui.tabWidget->addTab(pRender, tr("Scene"));
	m_pTabWidget = new QTabWidget;
	m_pTabWidget->addTab(pRender, tr("Scene"));
	m_pTabWidget->installEventFilter(this);
	setCentralWidget(m_pTabWidget);
	pRender->installEventFilter(this);

	//QtRenderView* pRender2 = new QtRenderView();
	//pRender2->m_strName = "Scene2";
	//pRender2->installEventFilter(this);
	//m_pTabWidget->addTab(pRender2, tr("Scene_2"));
	QTimer *timer = new QTimer(this); 
	//tool bar
	CreateToolBar();
	CreateMenuBar();
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
		m_pTreePropertyBrowser->SetTarget(EditorApplication::GetInstance()->getSelectObj());
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
	m_pSceneTreeView->setItemSelected(pRoot, true);
};

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
	EditorApplication::GetInstance()->SelectChange(pSceneItem->m_pObj);
	//std::cout << "Name:" << pSceneItem->m_pObj->m_strName << std::endl;
}

void QtEditor::CreateToolBar()
{
	m_pCommonToolBar = new CommonToolBar(tr("CommonToolBar"), this);
	addToolBar(Qt::LeftToolBarArea, m_pCommonToolBar);
}

void ZG::QtEditor::CreateMenuBar()
{
	connect(menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(onMenuActionTrigger(QAction*)));
	QMenu *m_pFileMenu = menuBar()->addMenu(tr("&File"));
	QAction *pLoadScene = m_pFileMenu->addAction(tr("Load Scene...Ctrl+O"));
	QAction *pSaveScene = m_pFileMenu->addAction(tr("Save Scene...Ctrl+S"));
	QAction *pSaveSceneAs = m_pFileMenu->addAction(tr("Save Scene As...Ctrl+Shift+S"));
	pLoadScene->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	pSaveScene->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	pSaveSceneAs->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
	m_mapMenuBarAction[pSaveScene] = "FILE_SAVE_SCENE";
	m_mapMenuBarAction[pLoadScene] = "FILE_LOAD_SCENE";
	m_mapMenuBarAction[pSaveSceneAs] = "FILE_SAVE_SCENE_AS";

	//Edit
	QMenu* m_pEditMenu = menuBar()->addMenu(tr("&Edit"));
	QAction* pUndo = m_pEditMenu->addAction(tr("Undo...Ctrl+Z"));
	QAction* pRedo = m_pEditMenu->addAction(tr("Redo...Ctrl+Y"));
	QAction* pDelete = m_pEditMenu->addAction(tr("Delete...Delete"));
	QAction* pFoucus = m_pEditMenu->addAction(tr("Focus...F"));
	pUndo->setShortcut(QKeySequence::Undo);
	pRedo->setShortcut(QKeySequence::Redo);
	pDelete->setShortcut(QKeySequence::Delete);
	pFoucus->setShortcut(Qt::Key_F);
	m_mapMenuBarAction[pUndo] = "EDIT_UNDO";
	m_mapMenuBarAction[pRedo] = "EDIT_REDO";
	m_mapMenuBarAction[pDelete] = "EDIT_DELETE";
	m_mapMenuBarAction[pFoucus] = "FOCUS_SELECT";
	
	//Tool
	QMenu* m_pToolMenu = menuBar()->addMenu(tr("&Tool"));
	QMenu* m_pFbxMenu = m_pToolMenu->addMenu(tr("&Fbx"));
	QAction* pExportAnimation = m_pFbxMenu->addAction("Export Animation");
	QAction* pExportAllAnimation = m_pFbxMenu->addAction("Export All Animation");
	m_mapMenuBarAction[pExportAnimation] = "TOOL_FBX_EXPORTANI";
	m_mapMenuBarAction[pExportAllAnimation] = "TOOL_FBX_EXPORTALLANI";

}

void ZG::QtEditor::onMenuActionTrigger(QAction* pAction)
{
	std::map<QAction*, std::string>::iterator iter = m_mapMenuBarAction.find(pAction);
	if (iter == m_mapMenuBarAction.end())
	{
		return;
	}
	if (iter->second == "FILE_SAVE_SCENE_AS")
	{
		QString fileName
			= QFileDialog::getSaveFileName(this, tr("Save Scene File"), "./data", tr("Scene (*.scene.xml *.scene)"));
		if (fileName.isEmpty())
			return;
		EditorApplication::GetInstance()->SaveScene(fileName.toStdString());
	}
	if (iter->second == "FILE_SAVE_SCENE")
	{
		QString fileName
			= QFileDialog::getSaveFileName(this, tr("Save Scene File"), "./data", tr("Scene (*.scene.xml *.scene)"));
		if (fileName.isEmpty())
			return;
		EditorApplication::GetInstance()->SaveScene(fileName.toStdString());
	}
	if (iter->second == "FILE_LOAD_SCENE")
	{
		QString fileName
			= QFileDialog::getOpenFileName(this, tr("Save Scene File"), "./data", tr("Scene (*.scene.xml *.scene)"));
		if (fileName.isEmpty())
			return;
		EditorApplication::GetInstance()->LoadScene(fileName.toStdString());
	}
	if (iter->second == "EDIT_UNDO")
	{
		EditorCommandManager::GetInstance()->Undo();
	}
	if (iter->second == "EDIT_REDO")
	{
		EditorCommandManager::GetInstance()->Redo();
	}
	if (iter->second == "EDIT_DELETE")
	{
		if (IsRenderViewActive() == true)
		{
			if (EditorApplication::GetInstance()->getSelectObj() != nullptr && EditorApplication::GetInstance()->getSelectObj()->GetParent() != nullptr)
			{
				DeleteCommand* pCmd = new DeleteCommand;
				pCmd->m_pObj = EditorApplication::GetInstance()->getSelectObj();
				pCmd->m_pParentObj = EditorApplication::GetInstance()->getSelectObj()->GetParent();
				pCmd->m_pReceiver = EditorApplication::GetInstance();
				EditorCommandManager::GetInstance()->ExcuteNewCmd(pCmd);
				

			}
		}
	}
	if (iter->second == "FOCUS_SELECT")
	{
		EditorSceneView* pSceneView = EditorApplication::GetInstance()->getActiveScene();
		if (pSceneView != nullptr)
		{
			pSceneView->FocusTarget(EditorApplication::GetInstance()->getSelectObj());
		}
	}
	if (iter->second == "TOOL_FBX_EXPORTANI")
	{
		QItemSelectionModel* selections = m_pDataView->selectionModel();
		QModelIndexList indexs = selections->selectedIndexes();
		int nCount = indexs.count();
		for (int i = 0; i < nCount; ++i)
		{
			QModelIndex pIndex = indexs[i];
			QVariant data = pIndex.data(QFileSystemModel::FilePathRole);
			std::string fbxPath = data.toString().toStdString();
			//
			std::string strSuffix = getFileSuffix(fbxPath);
			std::transform(strSuffix.begin(), strSuffix.end(), strSuffix.begin(), tolower);
			if (strSuffix != "fbx")
			{
				continue;
			}
			//
			IAsset* pFbx = AssetManager::GetInstance()->LoadAsset(fbxPath);
			if (pFbx == nullptr)
			{
				continue;
			}
			AnimationResource* pRes = pFbx->GetResource<AnimationResource>();
			if (pRes == nullptr)
			{
				pFbx->Release(true);
				continue;
			}
			//
			SingleResourceAsset* pTargetAsset = new SingleResourceAsset;
			pTargetAsset->AddResource("", pRes);
			pTargetAsset->m_strPath = getFileDirectory(fbxPath) + getFileNameWithoutSuffix(fbxPath) + ".animation.xml";
			AssetManager::GetInstance()->Save(pTargetAsset);
			//
			pFbx->Release(true);
			pTargetAsset->Release(true);
		}

	}
	if (iter->second == "TOOL_FBX_EXPORTALLANI")
	{
		QModelIndex pIndex = m_pDataView->m_pDirectoryView->currentIndex();
		QVariant data = pIndex.data(QFileSystemModel::FilePathRole);
		std::string fileDir = data.toString().toStdString();
		fileDir = fileDir + "/";
		//std::cout << "cur dir:" << fileDir.c_str() << std::endl;
		std::vector<std::string> vecFiles;
		FindFile(fileDir, vecFiles, "*.FBX");

		for (int i = 0; i < vecFiles.size(); ++i)
		{
			std::string fbxPath = vecFiles[i];
			IAsset* pFbx = AssetManager::GetInstance()->LoadAsset(fbxPath);
			if (pFbx == nullptr)
			{
				continue;
			}
			AnimationResource* pRes = pFbx->GetResource<AnimationResource>();
			if (pRes == nullptr)
			{
				pFbx->Release(true);
				continue;
			}
			//
			SingleResourceAsset* pTargetAsset = new SingleResourceAsset;
			pTargetAsset->AddResource("", pRes);
			pTargetAsset->m_strPath = fileDir + getFileNameWithoutSuffix(fbxPath) + ".animation.xml";
			AssetManager::GetInstance()->Save(pTargetAsset);
			//
			pFbx->Release(true);
			pTargetAsset->Release(true);

		}
	}
}

bool ZG::QtEditor::IsRenderViewActive() const
{
	return true;
}

void ZG::QtEditor::OnEditorUpdate(EditorUpdateArg& arg)
{
	m_pTreePropertyBrowser->UpdateProperty();
}

//void QtEditor::DataItemClicked(const QModelIndex &)
//{
//	std::cout << "data item clicked" << std::endl;
//}

//void QtEditor::valueChanged(QtProperty *pProp, const QVariant &variant)
//{
//
//}
