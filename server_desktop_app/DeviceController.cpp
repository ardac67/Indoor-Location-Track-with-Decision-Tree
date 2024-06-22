#include "DeviceController.h"
#include "mainwindow.h"
int counter111 =0;
QString model3d_adress;
DeviceController::DeviceController(int port, QObject *parent)
    : QObject{parent}
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &DeviceController::on_client_connecting);
    //connect(_server, &MainWindow::sendToAllClients, this, &DeviceController::sendMessageToClients);
    _isStarted = _server->listen(QHostAddress::Any, port);
    if(!_isStarted){
        qDebug() << "Server could not start";
    } else{
        qDebug() << "Server started...";
    }

}

void DeviceController::on_client_connecting()
{
    qDebug() << "a client connected to server";
    auto socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &DeviceController::clientDataReady);
    connect(socket, &QTcpSocket::disconnected, this, &DeviceController::clientDisconnected);
    if(counter111 == 0){
        model3d_adress =socket->peerAddress().toString();
    }
    counter111++;
    _socketsList.append(socket);
    //socket->write("Connection is established");
    emit newClientConnected();
}

void DeviceController::clientDisconnected()
{
    emit clientDisconnect();
}

void DeviceController::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    QString clientIp = socket->peerAddress().toString();
    emit dataReceived(data,clientIp);
}

bool DeviceController::isStarted() const
{
    return _isStarted;
}

void DeviceController::sendMessageToClients(QString data){
    foreach (auto socket, _socketsList) {
        if(data.contains("revive")){
            if(socket->peerAddress().toString() != model3d_adress ){
                socket->write(data.toUtf8());
            }
        }
        else{
            socket->write(data.toUtf8());
        }

    }
}

void DeviceController::sendDataToClient(QTcpSocket* clientSocket, const QString& data) {
    if (clientSocket && clientSocket->state() == QTcpSocket::ConnectedState) {
        clientSocket->write(data.toUtf8());
    }
}


