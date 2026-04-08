#include "mainwindow.h"
#include "pagetable.h"
#include <QApplication>
#include <QMetaType>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册跨线程 QueuedConnection 信号所需的自定义类型
    qRegisterMetaType<Page>("Page");
    qRegisterMetaType<QJsonObject>("QJsonObject");

    MainWindow w;
    w.show();
    return a.exec();
}
