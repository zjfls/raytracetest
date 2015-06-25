#include "stdafx.h"
#include "CommonToolBar.h"
#include <iostream>


CommonToolBar::CommonToolBar(const QString &title, QWidget *parent)
	:QToolBar(title,parent)
{
	setIconSize(QSize(32, 32));
	createAction();
}


CommonToolBar::~CommonToolBar()
{
}

void CommonToolBar::createAction()
{
	connect(this, SIGNAL(actionTriggered(QAction*)), this, SLOT(onActionTrigger(QAction*)));
	m_pSelectAction = new QAction(tr("Select"),this);
	m_pSelectAction->setCheckable(true);
	m_pSelectAction->setText(tr("Select"));
	QPixmap pixmap(":/QtEditor/EditorRes/Icon/pointer.png");
	m_pSelectAction->setIcon(pixmap);
	m_pSelectAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
	addAction(m_pSelectAction);
	m_mapActions["Select"] = m_pSelectAction;


	m_pMoveAction = new QAction(tr("Move"), this);
	m_pMoveAction->setCheckable(true);
	m_pMoveAction->setText(tr("Move"));
	QPixmap pixmapMove(":/QtEditor/EditorRes/Icon/move.png");
	m_pMoveAction->setIcon(pixmapMove);
	m_pMoveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
	addAction(m_pMoveAction);
	m_mapActions["Move"] = m_pMoveAction;

	
	m_pRotationAction = new QAction(tr("Rotate"), this);
	m_pRotationAction->setCheckable(true);
	m_pRotationAction->setText(tr("Rotate"));
	QPixmap pixmapRotate(":/QtEditor/EditorRes/Icon/rotate.png");
	m_pRotationAction->setIcon(pixmapRotate);
	m_pRotationAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
	addAction(m_pRotationAction);
	m_mapActions["Rotate"] = m_pRotationAction;

	m_pScaleAction = new QAction(tr("Scale"), this);
	m_pScaleAction->setCheckable(true);
	m_pScaleAction->setText(tr("Scale"));
	QPixmap pixmapScale(":/QtEditor/EditorRes/Icon/scale.png");
	m_pScaleAction->setIcon(pixmapScale);
	m_pScaleAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
	addAction(m_pScaleAction);
	m_mapActions["Scale"] = m_pScaleAction;
}

void ZG::CommonToolBar::onActionTrigger(QAction* pAction)
{
	if (pAction == nullptr)
	{
		return;
	}
	if (pAction == m_pSelectAction)
	{
		std::cout << "action select triggered" << std::endl;
	}
	else if (pAction == m_pMoveAction)
	{
		std::cout << "action move triggered" << std::endl;
	}
	else if (pAction == m_pRotationAction)
	{
		std::cout << "action rotation triggered" << std::endl;
	}
	else if (pAction == m_pScaleAction)
	{
		std::cout << "action scale triggered" << std::endl;
	}
	for each (std::pair<std::string,QAction*> p in m_mapActions)
	{
		if (p.second != pAction)
		{
			p.second->setChecked(false);
		}
	}
}
