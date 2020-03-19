#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->showMessage("Not Connected");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    this->statusBar()->showMessage("Connected");
}

void MainWindow::onDisconnect()
{
    this->statusBar()->showMessage("Disconnected");
}

void MainWindow::onTextRecieved(QString message)
{
    ui->rXplainTextEdit->appendPlainText(message);
}

void MainWindow::onBinaryRecieved(QByteArray message)
{
    qDebug()<<"Recieved: "<<message.size();
}

void MainWindow::on_connectButton_clicked()
{
    delete(ws);
    this->ws = new QWebSocket();
    connect(ws, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(ws, &QWebSocket::disconnected, this, &MainWindow::onDisconnect);
    connect(ws, &QWebSocket::textMessageReceived, this, &MainWindow::onTextRecieved);
    connect(ws, &QWebSocket::binaryMessageReceived, this, &MainWindow::onBinaryRecieved);

    ws->open(QUrl("ws://"+ui->addressLineEdit->text()));
}

void MainWindow::on_textSendButton_clicked()
{
    ws->sendTextMessage(ui->tXplainTextEdit->toPlainText());
}

void MainWindow::on_chooseFileButton_clicked()
{

    QFileDialog fD(this);
//    fD.exec();
    QFile file;
    file.setFileName(fD.getOpenFileName());
    file.open(QIODevice::ReadOnly);
    data.clear();
    data=file.readAll();
//    data.append(data);
//    data.append(data);
//    data.append(data);

    qDebug()<<data.size();
}

void MainWindow::on_fileSendButton_clicked()
{
    if(data.size()>1)
        ws->sendBinaryMessage(data);

}
