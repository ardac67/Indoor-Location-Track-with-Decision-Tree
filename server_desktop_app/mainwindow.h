#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DeviceController.h"
#include <QMainWindow>
#include "Game.h"
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void sendToAllClients(QString message);

private slots:
    void on_pushButton_clicked();
    void newClinetConnected();

    void clientDisconnected();

    void clientDataReceived(QString message,QString client_info);

    void sendAllClientSlot();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void clientJsonReceived(QString json);

    void create_player(QJsonObject message);
    void hit_player(QJsonDocument document);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    void set_location(QJsonObject location_message);

private:
    Ui::MainWindow *ui;
    DeviceController *_server;
    Game *game;
    QMap<QString, QProgressBar*> progressBarMap;

};


#endif
