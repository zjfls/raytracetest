#include "stdafx.h"
#include "QtRenderView.h"
#include "EditorSceneView.h"
#include "QEvent.h"
#include "QSize.h"
#include <iostream>
#include "EditorApplication.h"
#include "Vector2.h"
#include "PickUtil.h"
#include "qteditor.h"
#include "QListDataView.h"
QMenu* QtRenderView::m_spSceneMenu = nullptr;
//
QtRenderView::QtRenderView()
{
	m_pRenderView = new EditorSceneView();
	m_pRenderView->Create(100, 100, winId());
	EditorApplication::GetInstance()->AddView(winId(), m_pRenderView);
	setAcceptDrops(true);


	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(ShowContextMenu(const QPoint&)));

	if (m_spSceneMenu == nullptr)
	{
		m_spSceneMenu = new QMenu;
		QAction* pAction = m_spSceneMenu->addAction(tr("clone"));
		m_spSceneActions[pAction] = "SCENE_SELECTIONS_CLONE";
		connect(m_spSceneMenu, SIGNAL(triggered(QAction*)), this, SLOT(OnSceneMenuTriggered(QAction*)));
	}
	//
	QMenu myMenu;
}


QtRenderView::~QtRenderView()
{
}

void QtRenderView::resizeEvent(QResizeEvent * pEvent)
{
	if (m_pRenderView != nullptr)
	{
		//std::cout << m_strName.c_str()<< "width:" << pEvent->size().width() << "height:" << pEvent->size().height() << std::endl;
		m_pRenderView->Resize(pEvent->size().width(), pEvent->size().height());
	}
}

void QtRenderView::wheelEvent(QWheelEvent * event)
{
	Vector2 v;
	v.m_fx = event->pos().rx();
	v.m_fy = event->pos().ry();
	m_pRenderView->OnMouseWheel(event->delta(), v);
}

void QtRenderView::mousePressEvent(QMouseEvent * event)
{
	Vector2 v;
	v.m_fx = event->pos().rx();
	v.m_fy = event->pos().ry();
	m_nPtPressPos = event->pos();
	//
	Qt::MouseButton mb = event->button();
	Qt::MouseButton b = (Qt::MouseButton)(mb & Qt::MouseButton::RightButton);
	if (b != 0)
	{
		m_pRenderView->OnMouseRButtonDown(v);
	}
	b = (Qt::MouseButton)(mb & Qt::MouseButton::LeftButton);
	if (b != 0)
	{
		m_pRenderView->OnMouseLButtonDown(v);
	}
	b = (Qt::MouseButton)(mb & Qt::MouseButton::MidButton);
	if (b != 0)
	{
		m_pRenderView->OnMouseMButtonDown(v);
	}
	QWidget::mousePressEvent(event);
	setFocus();
}

void QtRenderView::mouseMoveEvent(QMouseEvent * event)
{
	Vector2 v;
	v.m_fx = event->pos().rx();
	v.m_fy = event->pos().ry();
	m_pRenderView->OnMouseMove(v);
}

void QtRenderView::mouseReleaseEvent(QMouseEvent * event)
{
	Vector2 v;
	v.m_fx = event->pos().rx();
	v.m_fy = event->pos().ry();
	if (event->button() & Qt::LeftButton)
	{
		QPoint diff = m_nPtPressPos - event->pos();
		//
		if (abs(diff.x()) < 2 && abs(diff.y()) < 2)
		{
			m_pRenderView->OnClick(v);
		}
		m_pRenderView->OnMouseLButtonRelease(v);
	}
}


void QtRenderView::keyPressEvent(QKeyEvent * event)
{
	int key = event->key();
	m_pRenderView->OnKeyPressed(key);
}

void QtRenderView::dragEnterEvent(QDragEnterEvent *event)
{
	QtEditor* pEditor = (QtEditor*)EditorApplication::GetInstance()->m_pEditorApp;

	
	if (event->source() == pEditor->m_pDataView)
	{
		QList<QUrl> urls = event->mimeData()->urls();
		QUrl u = urls.at(0);
		std::cout << u.toString().toStdString().c_str() << std::endl;
		//std::cout << "drag enter" << std::endl;
		int nWidth = width();
		int nHeight = height();
		Vector2 screenPos(event->pos().x(), event->pos().y());
		m_pRenderView->OnDragEnter(screenPos,u.toString().toStdString());
		event->accept();
		
		//Vector3 pos = PickUtil::ScreenPosToWorldPos(screenPos, 500.0f, nullptr, nWidth, nHeight);
	}

}

void QtRenderView::dragMoveEvent(QDragMoveEvent *event)
{

}

void QtRenderView::dropEvent(QDropEvent *event)
{
	QtEditor* pEditor = (QtEditor*)EditorApplication::GetInstance()->m_pEditorApp;
	if (event->source() == pEditor->m_pDataView)
	{
		QList<QUrl> urls = event->mimeData()->urls();
		QUrl u = urls.at(0);
		std::cout << u.toString().toStdString().c_str() << std::endl;
		//std::cout << "drag enter" << std::endl;
		int nWidth = width();
		int nHeight = height();
		Vector2 screenPos(event->pos().x(), event->pos().y());
		m_pRenderView->OnDrop(screenPos, u.toString().toStdString());
		event->accept();

		//Vector3 pos = PickUtil::ScreenPosToWorldPos(screenPos, 500.0f, nullptr, nWidth, nHeight);
	}
}

void QtRenderView::focusInEvent(QFocusEvent *)
{
	//std::cout << "focus in" << std::endl;
	m_pRenderView->m_bIsFocus = true;

}

void QtRenderView::focusOutEvent(QFocusEvent *)
{
	//std::cout << "focus out" << std::endl;
	m_pRenderView->m_bIsFocus = false;
}

void QtRenderView::showEvent(QShowEvent *)
{
	m_pRenderView->m_bShow = true;
	m_pRenderView->Resize(size().rwidth(), size().rheight());
	//std::cout << "show" << std::endl;
}

void QtRenderView::hideEvent(QHideEvent *)
{
	m_pRenderView->m_bShow = false;
	//std::cout << "hide" << std::endl;
}

void ZG::QtRenderView::ShowContextMenu(const QPoint& pos)
{
	//std::cout << "menu" << std::endl;
	QPoint globalPos = mapToGlobal(pos);
	// for QAbstractScrollArea and derived classes you would use:
	// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);



	m_spSceneMenu->exec(globalPos);
	//QMenu myMenu;
	//myMenu.addAction("Menu Item 1");
	//// ...

	//QAction* selectedItem = myMenu.exec(globalPos);
	//if (selectedItem)
	//{
	//	// something was chosen, do stuff
	//}
	//else
	//{
	//	// nothing was chosen
	//}
}

void ZG::QtRenderView::OnSceneMenuTriggered(QAction* pAction)
{
	if (m_spSceneActions[pAction] == "SCENE_SELECTIONS_CLONE")
	{
		EditorApplication::GetInstance()->CloneSelections();
	}
}

//bool QtRenderView::event(QEvent *event)
//{
//	if (event->type() == QEvent::KeyPress) {
//		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
//		keyPressEvent(ke);
//	}
//
//	return QWidget::event(event);
//}