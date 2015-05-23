#include "stdafx.h"
#include "QtRenderView.h"
#include "EditorSceneView.h"
#include "QEvent.h"
#include "QSize.h"
#include <iostream>
#include "EditorApplication.h"
#include "Vector2.h"
QtRenderView::QtRenderView()
{
	m_pRenderView = new EditorSceneView();
	m_pRenderView->Create(10, 10, winId());
	EditorApplication::GetInstance()->AddView(winId(), m_pRenderView);
}


QtRenderView::~QtRenderView()
{
}

void QtRenderView::resizeEvent(QResizeEvent * pEvent)
{
	if (m_pRenderView != nullptr)
	{
		std::cout << "width:" << pEvent->size().width() << "height:" << pEvent->size().height() << std::endl;
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

}

void QtRenderView::keyPressEvent(QKeyEvent * event)
{
	int key = event->key();
	m_pRenderView->OnKeyPressed(key);
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