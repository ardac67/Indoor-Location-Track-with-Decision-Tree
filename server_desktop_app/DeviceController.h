#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(int port, QObject *parent = nullptr);
    bool isStarted() const;
    void sendMessageToClients(QString data);
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message,QString clientIp);
    void sendData();


private slots:
    void on_client_connecting();

    void clientDisconnected();

    void clientDataReady();


    //not implemented yet
    void sendDataToClient(QTcpSocket* clientSocket, const QString& data);







private:
    QTcpServer *_server;
    QList<QTcpSocket *> _socketsList;
    bool _isStarted;
};

#endif
