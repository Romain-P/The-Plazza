/********************************************************************************
** Form generated from reading UI file 'plazzagui.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAZZAGUI_H
#define UI_PLAZZAGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlazzaGUI
{
public:
    QWidget *centralWidget;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PlazzaGUI)
    {
        if (PlazzaGUI->objectName().isEmpty())
            PlazzaGUI->setObjectName(QStringLiteral("PlazzaGUI"));
        PlazzaGUI->resize(400, 300);
        centralWidget = new QWidget(PlazzaGUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(140, 110, 118, 23));
        progressBar->setValue(24);
        PlazzaGUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PlazzaGUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 19));
        PlazzaGUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlazzaGUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PlazzaGUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PlazzaGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PlazzaGUI->setStatusBar(statusBar);

        retranslateUi(PlazzaGUI);

        QMetaObject::connectSlotsByName(PlazzaGUI);
    } // setupUi

    void retranslateUi(QMainWindow *PlazzaGUI)
    {
        PlazzaGUI->setWindowTitle(QApplication::translate("PlazzaGUI", "PlazzaGUI", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlazzaGUI: public Ui_PlazzaGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAZZAGUI_H
