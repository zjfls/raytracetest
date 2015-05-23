#include "stdafx.h"
#include "CommonToolBar.h"


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
	m_pSelectAction = new QAction(tr("Select"),this);
	m_pSelectAction->setCheckable(true);
	m_pSelectAction->setText(tr("Select"));
	QPixmap pixmap(":/QtEditor/EditorRes/Icon/pointer.png");
	m_pSelectAction->setIcon(pixmap);
	m_pSelectAction->setShortcut(tr("Ctrl+B"));
	addAction(m_pSelectAction);

	m_pMoveAction = new QAction(tr("Move"), this);
	m_pMoveAction->setCheckable(true);
	m_pMoveAction->setText(tr("Move"));
	QPixmap pixmapMove(":/QtEditor/EditorRes/Icon/move.png");
	m_pMoveAction->setIcon(pixmapMove);
	m_pMoveAction->setShortcut(tr("Ctrl+W"));
	addAction(m_pMoveAction);

	
	m_pRotationAction = new QAction(tr("Rotate"), this);
	m_pRotationAction->setCheckable(true);
	m_pRotationAction->setText(tr("Rotate"));
	QPixmap pixmapRotate(":/QtEditor/EditorRes/Icon/rotate.png");
	m_pRotationAction->setIcon(pixmapRotate);
	m_pRotationAction->setShortcut(tr("Ctrl+R"));
	addAction(m_pRotationAction);

	m_pScaleAction = new QAction(tr("Scale"), this);
	m_pScaleAction->setCheckable(true);
	m_pScaleAction->setText(tr("Scale"));
	QPixmap pixmapScale(":/QtEditor/EditorRes/Icon/scale.png");
	m_pScaleAction->setIcon(pixmapScale);
	m_pScaleAction->setShortcut(tr("Ctrl+E"));
	addAction(m_pScaleAction);
}
