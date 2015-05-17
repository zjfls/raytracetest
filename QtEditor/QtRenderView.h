#pragma once
#include "qwidget.h"
class EditorRenderView;
class QtRenderView :
	public QWidget
{
	Q_OBJECT
public:
	QtRenderView();
	virtual ~QtRenderView();
	//virtual void paintEvent(QPaintEvent *);
	virtual void	resizeEvent(QResizeEvent * event);
	virtual void	wheelEvent(QWheelEvent * event);
	virtual void	mousePressEvent(QMouseEvent * event);
	virtual void	mouseMoveEvent(QMouseEvent * event);
	virtual void	mouseReleaseEvent(QMouseEvent * event);
	virtual void	keyPressEvent(QKeyEvent * event);
	//virtual bool	event(QEvent* evt);
	EditorRenderView* m_pRenderView;
};
