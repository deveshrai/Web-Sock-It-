#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QFileDialog>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnected();
    void onDisconnect();
    void onTextRecieved(QString message);
    void onBinaryRecieved(QByteArray message);

    void on_connectButton_clicked();

    void on_textSendButton_clicked();

    void on_chooseFileButton_clicked();

    void on_fileSendButton_clicked();

private:
    Ui::MainWindow *ui;
    QWebSocket *ws;
    QByteArray data;
};

#endif // MAINWINDOW_H
