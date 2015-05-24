#pragma once
#include "QListView.h"
class QListDataView:public QListView
{
	Q_OBJECT
public:
	QListDataView();
	virtual ~QListDataView();
	private slots:
	void DataItemDoubleClicked(const QModelIndex &index);
	void DirectoryDoubleClicked(const QModelIndex &index);

public:
	QTreeView* m_pDirectoryView;
};

