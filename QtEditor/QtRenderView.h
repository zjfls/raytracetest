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


	virtual void focusInEvent(QFocusEvent *);
	virtual void focusOutEvent(QFocusEvent *);
	//
	virtual void showEvent(QShowEvent *);
	virtual void hideEvent(QHideEvent *);


	//
	void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
	//
	//virtual bool	event(QEvent* evt);
	EditorRenderView* m_pRenderView;


	//
	QPoint m_nPtPressPos;
	//int m_nMousePressPosX;
	//int m_nMousePressPosY;
	//
};

