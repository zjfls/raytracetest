#include "stdafx.h"
#include "qteditor.h"
#include "EditorApplication.h"
#include "QtRenderView.h"

QtEditor::QtEditor(QWidget *parent)
	: QMainWindow(parent)
{
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

	QDockWidget *dock = new QDockWidget(tr("Customers"), this);
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


	QtRenderView* pRender = new QtRenderView();
	//setCentralWidget(pRender);
	//ui.tabWidget->addTab(pRender, tr("Scene"));
	m_pTabWidget = new QTabWidget;
	m_pTabWidget->addTab(pRender, tr("Scene"));
	setCentralWidget(m_pTabWidget);


	QtRenderView* pRender2 = new QtRenderView();
	m_pTabWidget->addTab(pRender2, tr("Scene_2"));
	QTimer *timer = new QTimer(this); 

	//�½���ʱ��

	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));

	//������ʱ�������źź���Ӧ�Ĳۺ���

	timer->start(0);
}

QtEditor::~QtEditor()
{

}

void QtEditor::OnNotify(std::string msg, std::shared_ptr<IListenerSubject> pSubject)
{

}

void QtEditor::OnTimer()
{
	EditorApplication::GetInstance()->Run();
}
