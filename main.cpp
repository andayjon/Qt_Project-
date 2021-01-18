#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{

    QTextCodec *codec = QTextCodec::codecForName("GBK");//修改这两行
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
