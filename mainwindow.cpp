#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qftp.h"
#include <qtextcodec.h>
#include <QTextCodec>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ftp = new QFtp(this);
//    ftp->connectToHost("v0.ftp.upyun.com");
//    ftp->login("qtertest/qtftptest", "pwd123456");
//    ftp->get("readme.txt");
    ftp->connectToHost("39.102.43.157");
    ftp->login("zhang", "zhang123456");
    ftp->get("/1.txt");
    ftp->close();
    connect(ftp, &QFtp::commandStarted,
            this, &MainWindow::ftpCommandStarted);
    connect(ftp, &QFtp::commandFinished,
            this, &MainWindow::ftpCommandFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ftpCommandStarted(int)
{
    int id = ftp->currentCommand();
    switch (id)
    {
    case QFtp::ConnectToHost :
        ui->label->setText(tr("正在连接到服务器…"));
        qDebug()<< QString("正在连接到服务器…") <<endl;
        break;
    case QFtp::Login :
        ui->label->setText(tr("正在登录…"));
        qDebug()<< QString("正在登录…") <<endl;
        break;
    case QFtp::Get :
        ui->label->setText(tr("正在下载…"));
        break;
    case QFtp::Close :
        ui->label->setText(tr("正在关闭连接…"));
    }
}

void MainWindow::ftpCommandFinished(int, bool error)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost) {
        if (error) {
            ui->label->setText(tr("连接服务器出现错误：%1").arg(ftp->errorString()));
            qDebug()<< QString("连接服务器出现错误：%1").arg(ftp->errorString()) <<endl;
        }else {
            ui->label->setText(tr("连接到服务器成功"));
            qDebug()<< QString("连接到服务器成功") <<endl;
        }
    } else if (ftp->currentCommand() == QFtp::Login) {
        if(error) {
            ui->label->setText(tr("登录出现错误：%1").arg(ftp->errorString()));
            qDebug()<< QString("登录出现错误：%1").arg(ftp->errorString()) <<endl;
        }else {
            ui->label->setText(tr("登录成功"));
            qDebug()<< QString("登录成功") <<endl;
        }
    } else if (ftp->currentCommand() == QFtp::Get) {
        if(error)
            ui->label->setText(tr("下载出现错误：%1").arg(ftp->errorString()));
        else {
            ui->label->setText(tr("已经完成下载"));
            QTextCodec *codec = QTextCodec::codecForName("GBK");//修改这两行
//            QTextCodec *codec = QTextCodec::codecForLocale();
            ui->textBrowser->setText(codec->toUnicode(ftp->readAll()));
        }
    } else if (ftp->currentCommand() == QFtp::Close) {
        ui->label->setText(tr("已经关闭连接"));
    }
}
