#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "historycalendardialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDate>
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 创建测试按钮
    m_testButton = new QPushButton("打开日历对话框", this);
    m_testButton->setGeometry(50, 50, 200, 50);
    m_testButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1976D2;"
        "}"
    );
    
    connect(m_testButton, &QPushButton::clicked, this, &MainWindow::openCalendarDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openCalendarDialog()
{
    HistoryCalendarDialog dialog(this);
    
    // 设置一些测试的历史日期
    QSet<QDate> availableDates;
    QDate currentDate = QDate::currentDate();
    
    // 添加当前月份的一些日期作为历史记录
    for (int day = 1; day <= 10; ++day) {
        availableDates.insert(QDate(currentDate.year(), currentDate.month(), day));
    }
    
    // 添加下个月的一些日期
    QDate nextMonth = currentDate.addMonths(1);
    for (int day = 1; day <= 5; ++day) {
        availableDates.insert(QDate(nextMonth.year(), nextMonth.month(), day));
    }
    
    // 设置可用日期
    dialog.setAvailableDates(availableDates);
    
    // 设置默认选中今天
    dialog.setSelectedDate(currentDate);
    
    // 显示模态对话框
    if (dialog.exec() == QDialog::Accepted) {
        QDate selectedDate = dialog.selectedDate();
        m_testButton->setText(QString("选中日期: %1").arg(selectedDate.toString("yyyy-MM-dd")));
    }
}
