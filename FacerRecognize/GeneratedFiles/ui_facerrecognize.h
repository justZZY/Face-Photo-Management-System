/********************************************************************************
** Form generated from reading UI file 'facerrecognize.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACERRECOGNIZE_H
#define UI_FACERRECOGNIZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FacerRecognizeClass
{
public:
    QAction *actionOpen;
    QAction *actionOpen_File;
    QAction *actionOpen_Dictionary;
    QAction *actionClose;
    QAction *actionEf;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *FacerRecognizeClass)
    {
        if (FacerRecognizeClass->objectName().isEmpty())
            FacerRecognizeClass->setObjectName(QStringLiteral("FacerRecognizeClass"));
        FacerRecognizeClass->resize(600, 400);
        actionOpen = new QAction(FacerRecognizeClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen_File = new QAction(FacerRecognizeClass);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionOpen_Dictionary = new QAction(FacerRecognizeClass);
        actionOpen_Dictionary->setObjectName(QStringLiteral("actionOpen_Dictionary"));
        actionClose = new QAction(FacerRecognizeClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionEf = new QAction(FacerRecognizeClass);
        actionEf->setObjectName(QStringLiteral("actionEf"));
        centralWidget = new QWidget(FacerRecognizeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FacerRecognizeClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FacerRecognizeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FacerRecognizeClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(FacerRecognizeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        FacerRecognizeClass->setMenuBar(menuBar);

        retranslateUi(FacerRecognizeClass);

        QMetaObject::connectSlotsByName(FacerRecognizeClass);
    } // setupUi

    void retranslateUi(QMainWindow *FacerRecognizeClass)
    {
        FacerRecognizeClass->setWindowTitle(QApplication::translate("FacerRecognizeClass", "FacerRecognize", 0));
        actionOpen->setText(QApplication::translate("FacerRecognizeClass", "Open", 0));
        actionOpen_File->setText(QApplication::translate("FacerRecognizeClass", "Open File", 0));
        actionOpen_Dictionary->setText(QApplication::translate("FacerRecognizeClass", "Open Dictionary", 0));
        actionClose->setText(QApplication::translate("FacerRecognizeClass", "Close", 0));
        actionEf->setText(QApplication::translate("FacerRecognizeClass", "ef", 0));
    } // retranslateUi

};

namespace Ui {
    class FacerRecognizeClass: public Ui_FacerRecognizeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACERRECOGNIZE_H
