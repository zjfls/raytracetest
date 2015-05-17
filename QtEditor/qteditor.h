#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_qteditor.h"
#include "IListener.h"

class QtEditor : public QMainWindow,public IListener
{
	Q_OBJECT

public:
	QtEditor(QWidget *parent = 0);
	~QtEditor();
	virtual void OnNotify(std::string msg, std::shared_ptr<IListenerSubject> pSubject);

	private slots:

	void OnTimer();
private:
	Ui::QtEditorClass ui;
	QTabWidget* m_pTabWidget;
};

#endif // QTEDITOR_H
