/********************************************************************************
** Form generated from reading UI file 'qteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEDITOR_H
#define UI_QTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtEditorClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QListView *listView;

    void setupUi(QMainWindow *QtEditorClass)
    {
        if (QtEditorClass->objectName().isEmpty())
            QtEditorClass->setObjectName(QStringLiteral("QtEditorClass"));
        QtEditorClass->resize(1600, 900);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtEditorClass->sizePolicy().hasHeightForWidth());
        QtEditorClass->setSizePolicy(sizePolicy);
        QtEditorClass->setTabShape(QTabWidget::Rounded);
        QtEditorClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        centralWidget = new QWidget(QtEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1600, 23));
        QtEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtEditorClass->setStatusBar(statusBar);
        dockWidget_2 = new QDockWidget(QtEditorClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidget_2->setMinimumSize(QSize(80, 180));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        listView = new QListView(dockWidgetContents_2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 0, 1920, 1080));
        dockWidget_2->setWidget(dockWidgetContents_2);
        QtEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_2);

        retranslateUi(QtEditorClass);

        QMetaObject::connectSlotsByName(QtEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtEditorClass)
    {
        QtEditorClass->setWindowTitle(QApplication::translate("QtEditorClass", "QtEditor", 0));
        dockWidget_2->setWindowTitle(QApplication::translate("QtEditorClass", "Output", 0));
#ifndef QT_NO_ACCESSIBILITY
        listView->setAccessibleName(QApplication::translate("QtEditorClass", "Output", 0));
#endif // QT_NO_ACCESSIBILITY
    } // retranslateUi

};

namespace Ui {
    class QtEditorClass: public Ui_QtEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEDITOR_H
