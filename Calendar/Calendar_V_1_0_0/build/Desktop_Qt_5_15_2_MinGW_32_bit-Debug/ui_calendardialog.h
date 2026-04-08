/********************************************************************************
** Form generated from reading UI file 'calendardialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARDIALOG_H
#define UI_CALENDARDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CalendarDialog
{
public:
    QVBoxLayout *mainLayout;
    QLabel *labelTitle;
    QHBoxLayout *comboLayout;
    QComboBox *comboYear;
    QComboBox *comboMonth;
    QSpacerItem *comboSpacer;
    QCalendarWidget *calendarWidget;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *btnCancel;
    QPushButton *btnConfirm;

    void setupUi(QDialog *CalendarDialog)
    {
        if (CalendarDialog->objectName().isEmpty())
            CalendarDialog->setObjectName(QString::fromUtf8("CalendarDialog"));
        CalendarDialog->resize(500, 450);
        CalendarDialog->setModal(true);
        mainLayout = new QVBoxLayout(CalendarDialog);
        mainLayout->setSpacing(15);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(20, 20, 20, 20);
        labelTitle = new QLabel(CalendarDialog);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QFont font;
        font.setPointSize(12);
        labelTitle->setFont(font);

        mainLayout->addWidget(labelTitle);

        comboLayout = new QHBoxLayout();
        comboLayout->setSpacing(20);
        comboLayout->setObjectName(QString::fromUtf8("comboLayout"));
        comboYear = new QComboBox(CalendarDialog);
        comboYear->setObjectName(QString::fromUtf8("comboYear"));
        comboYear->setMinimumSize(QSize(120, 40));
        QFont font1;
        font1.setPointSize(11);
        comboYear->setFont(font1);

        comboLayout->addWidget(comboYear);

        comboMonth = new QComboBox(CalendarDialog);
        comboMonth->setObjectName(QString::fromUtf8("comboMonth"));
        comboMonth->setMinimumSize(QSize(120, 40));
        comboMonth->setFont(font1);

        comboLayout->addWidget(comboMonth);

        comboSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        comboLayout->addItem(comboSpacer);


        mainLayout->addLayout(comboLayout);

        calendarWidget = new QCalendarWidget(CalendarDialog);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(0, 280));
        calendarWidget->setGridVisible(true);
        calendarWidget->setNavigationBarVisible(false);

        mainLayout->addWidget(calendarWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        btnCancel = new QPushButton(CalendarDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(100, 40));

        buttonLayout->addWidget(btnCancel);

        btnConfirm = new QPushButton(CalendarDialog);
        btnConfirm->setObjectName(QString::fromUtf8("btnConfirm"));
        btnConfirm->setMinimumSize(QSize(100, 40));

        buttonLayout->addWidget(btnConfirm);


        mainLayout->addLayout(buttonLayout);


        retranslateUi(CalendarDialog);

        QMetaObject::connectSlotsByName(CalendarDialog);
    } // setupUi

    void retranslateUi(QDialog *CalendarDialog)
    {
        CalendarDialog->setWindowTitle(QCoreApplication::translate("CalendarDialog", "\351\200\211\346\213\251\346\227\245\346\234\237", nullptr));
        labelTitle->setText(QCoreApplication::translate("CalendarDialog", "\351\200\211\346\213\251\345\217\221\351\200\201\346\227\245\346\234\237", nullptr));
        btnCancel->setText(QCoreApplication::translate("CalendarDialog", "\345\217\226\346\266\210", nullptr));
        btnConfirm->setText(QCoreApplication::translate("CalendarDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalendarDialog: public Ui_CalendarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARDIALOG_H
