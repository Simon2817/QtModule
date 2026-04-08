/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "LoggerWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *controlGroup;
    QHBoxLayout *controlLayout;
    QLabel *intervalLabel;
    QSpinBox *intervalSpinBox;
    QLabel *levelLabel;
    QComboBox *levelComboBox;
    QPushButton *startStopButton;
    QSpacerItem *horizontalSpacer;
    QLabel *statusLabel;
    LoggerWidget *loggerWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        controlGroup = new QGroupBox(centralwidget);
        controlGroup->setObjectName(QString::fromUtf8("controlGroup"));
        controlLayout = new QHBoxLayout(controlGroup);
        controlLayout->setObjectName(QString::fromUtf8("controlLayout"));
        intervalLabel = new QLabel(controlGroup);
        intervalLabel->setObjectName(QString::fromUtf8("intervalLabel"));

        controlLayout->addWidget(intervalLabel);

        intervalSpinBox = new QSpinBox(controlGroup);
        intervalSpinBox->setObjectName(QString::fromUtf8("intervalSpinBox"));
        intervalSpinBox->setMinimum(100);
        intervalSpinBox->setMaximum(60000);
        intervalSpinBox->setSingleStep(100);
        intervalSpinBox->setValue(1000);

        controlLayout->addWidget(intervalSpinBox);

        levelLabel = new QLabel(controlGroup);
        levelLabel->setObjectName(QString::fromUtf8("levelLabel"));

        controlLayout->addWidget(levelLabel);

        levelComboBox = new QComboBox(controlGroup);
        levelComboBox->addItem(QString());
        levelComboBox->addItem(QString());
        levelComboBox->addItem(QString());
        levelComboBox->addItem(QString());
        levelComboBox->setObjectName(QString::fromUtf8("levelComboBox"));

        controlLayout->addWidget(levelComboBox);

        startStopButton = new QPushButton(controlGroup);
        startStopButton->setObjectName(QString::fromUtf8("startStopButton"));

        controlLayout->addWidget(startStopButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controlLayout->addItem(horizontalSpacer);

        statusLabel = new QLabel(controlGroup);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        controlLayout->addWidget(statusLabel);


        verticalLayout->addWidget(controlGroup);

        loggerWidget = new LoggerWidget(centralwidget);
        loggerWidget->setObjectName(QString::fromUtf8("loggerWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(loggerWidget->sizePolicy().hasHeightForWidth());
        loggerWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(loggerWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 960, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RunningLogger \346\265\213\350\257\225", nullptr));
        controlGroup->setTitle(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\206\231\345\205\245\346\216\247\345\210\266", nullptr));
        intervalLabel->setText(QCoreApplication::translate("MainWindow", "\351\227\264\351\232\224 (ms)\357\274\232", nullptr));
        levelLabel->setText(QCoreApplication::translate("MainWindow", "\347\272\247\345\210\253\357\274\232", nullptr));
        levelComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "info", nullptr));
        levelComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "warn", nullptr));
        levelComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "error", nullptr));
        levelComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "\351\232\217\346\234\272", nullptr));

        startStopButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\345\206\231\345\205\245", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232\345\267\262\345\201\234\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
