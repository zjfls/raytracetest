#include "stdafx.h"
#include "QListDataView.h"
#include <iostream>

QListDataView::QListDataView()
{
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(DataItemDoubleClicked(const QModelIndex &)));
	setDragEnabled(true);
}


QListDataView::~QListDataView()
{
}

void QListDataView::DataItemDoubleClicked(const QModelIndex &index)
{
	//std::cout << "item double clicked" << std::endl;
	QFileSystemModel* pModel = (QFileSystemModel*)model();
	QVariant pData = pModel->data(index, QFileSystemModel::FilePathRole);
	
	
	QFileInfo fileInfo(pData.toString());
	if (fileInfo.isDir())
	{
		pModel->setRootPath(pData.toString());
		setRootIndex(index);
	}
	//if ()
}

void QListDataView::DirectoryDoubleClicked(const QModelIndex &index)
{
	QFileSystemModel* pTreeModel = (QFileSystemModel*)m_pDirectoryView->model();
	QFileSystemModel* pFileModel = (QFileSystemModel*)model();
	QString pPath = pTreeModel->data(index, QFileSystemModel::FilePathRole).toString();

	pFileModel->setRootPath(pPath);
	setRootIndex(pFileModel->index(pPath));
}
