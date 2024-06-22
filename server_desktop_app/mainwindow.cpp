#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"
#include "qrandom.h"
#include <QProcess>
#include <QVBoxLayout>
#include <classifier.h>
#include <QNetworkInterface>
#include <QDialog>
int counter = 0;
int team_set=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server =nullptr;
    if (_server == nullptr) {
        auto port =8080;
        _server = new DeviceController(port);
        this->game = new Game();
        connect(_server, &DeviceController::newClientConnected, this, &MainWindow::newClinetConnected);
        connect(_server, &DeviceController::dataReceived, this, &MainWindow::clientDataReceived);
        connect(_server, &DeviceController::clientDisconnect, this, &MainWindow::clientDisconnected);
        connect(this, &MainWindow::sendToAllClients, _server, &DeviceController::sendMessageToClients);
        ui->server_check_box_2->setDisabled(true);

        ui->port_label->setText(QString::number(8080));
        ui->server_check_box->setChecked(_server->isStarted());
        ui->server_check_box->setEnabled(false);
        ui->playerTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        ui->playerTable->setColumnCount(6);  // Four columns
        QStringList headers = {"Player Name", "PASSOUT", "KNOCKOUT", "Team","Health","id"};
        ui->playerTable->setHorizontalHeaderLabels(headers);
        ui->playerTable->setRowCount(4);
        ui->playerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->playerTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->playerTable->setStyleSheet(
            "QTableWidget {"
            "   border: none;"
            "   gridline-color: #dcdcdc;"
            "}"
            "QHeaderView::section {"
            "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f0f0f0, stop:1 #e0e0e0);"
            "   color: #333333;"
            "   padding: 5px;"
            "   border: 1px solid #cccccc;"
            "   font-size: 14px;"
            "   font-weight: bold;"
            "   text-transform: uppercase;"
            "}"
            "QTableWidget::item {"
            "   padding: 12px;"
            "   background-color: #ffffff;"
            "   color: #555555;"
            "}"
            "QTableWidget::item:selected {"
            "   background-color: #b6d7a8;"
            "   color: #ffffff;"
            "}"
            );
        //ui->progressBar->setValue(100);
        ui->pushButton->setDisabled(true);

        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

        for (const QNetworkInterface& interface : interfaces) {
            if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
                !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
                for (const QNetworkAddressEntry& entry : interface.addressEntries()) {
                    if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        qDebug() << interface.name() << "=>" << entry.ip().toString();
                        // Check for typical wireless interface names in Linux
                        if (interface.name().startsWith("wlan") ||
                            interface.name().startsWith("wifi") ||
                            interface.name().startsWith("wl")) {
                            ui->label_9->setText(entry.ip().toString());
                        }
                    }
                }
            }
        }
        qDebug() << game->returnGameStartorNot();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newClinetConnected()
{
    ui->listWidget->addItem("New Client connected");
}

void MainWindow::clientDisconnected()
{
    ui->listWidget->addItem("New Client Disconnected");
}

void MainWindow::clientDataReceived(QString message,QString client_info)
{
    ui->listWidget_3->addItem(message);
    ui->listWidget_3->addItem(client_info);
    clientJsonReceived(message);
}

void MainWindow::clientJsonReceived(QString message){
    QByteArray jsonData = message.toUtf8();
    QString message_type;
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject obj = document.object();
    if (!document.isNull() && document.isObject()) {
        message_type = obj["requestType"].toString();
    } else {
        qDebug() << "Failed to create JSON doc.";
    }
    if(message_type == "apk_player_create" && game->returnGameStartorNot() == false){
        //example of json :{"type": "player_create", "name": "messi", "team": "0"}
        create_player(obj);
    }
    else if(message_type == "hit" && game->returnGameStartorNot() == true){
        hit_player(document);
    }
    else if(message_type == "connect"){
        //connect_to_game(document);
    }
    else if(message_type == "disconnect"){
        //disconnected_from_game(object);
    }
    else if(message_type == "RSSI"  && /*game->returnPlayerCount() == 4*/ game->returnGameStartorNot() == true){
        set_location(obj);
    }
}

void MainWindow::set_location(QJsonObject location_message){
    if (location_message.contains("requestType") && location_message["requestType"].isString()) {
        QString requestType = location_message["requestType"].toString();
        qDebug() << "Request Type:" << requestType;
    } else {
        qDebug() << "Invalid or missing requestType";
        return;
    }
    QString id = location_message["id"].toString();
    qDebug() << "Güzel IDM:" << id;
    if (location_message.contains("RSSI") && location_message["RSSI"].isArray()) {
        QJsonArray rssiArray = location_message["RSSI"].toArray();
        const int maxSize = 40; // Define the maximum size of your array
        float rssiValues[maxSize] = {0};
        int count = qMin(rssiArray.size(), maxSize); // Ensure we do not exceed the array size

        for (int i = 0; i < count; ++i) {
            if (rssiArray[i].isDouble()) {
                rssiValues[i] = static_cast<float>(rssiArray[i].toDouble());
            }
        }

        int final_index=-1;
        float temp = -200;
        for(int i = 0 ; i<count;i++){
            if(temp < rssiValues[i] && rssiValues[i]!=0){
                temp = rssiValues[i];
                final_index=i;
            }
        }

        Classifier classifier1;
        int prediction = classifier1.predict(rssiValues);
        int test = final_index;
        if(prediction == test){
            qDebug() << prediction;
        }
       // ui->listWidget->addItem(QString::number(test));

        // Print the RSSI values
        qDebug() << "RSSI Values:";
        for (int i = 0; i < count; ++i) {
            qDebug() << rssiValues[i];
        }
        qDebug() << "Test Value:";
        qDebug() << test;
        QString random_location;
        switch (test) {
        case 0:
        {
            random_location = "a1";
            break;
        }
        case 1: random_location = "a2";
            break;
        case 2: random_location = "a3";
            break;
        case 3: random_location = "a4";
            break;
        case 4: random_location = "a5";
            break;
        case 5: random_location = "a6";
            break;
        case 6: random_location = "a7";
            break;
        case 7: random_location = "a8";
            break;
        case 8: random_location = "b1";
            break;
        case 9: random_location = "b2";
            break;
        }
        ui->listWidget->addItem("Id:"+id+" "+"Location: " +random_location + " RSSI:"+ QString::number(rssiValues[0])+" | " +QString::number(rssiValues[1])+ " | " +
                                QString::number(rssiValues[2])+ " | " +QString::number(rssiValues[3])+ " | " +QString::number(rssiValues[4])+ " | " +
    QString::number(rssiValues[5])+ " | " +QString::number(rssiValues[6])+ " | " +QString::number(rssiValues[7])+ " | " +QString::number(rssiValues[8])
                                + " | " +QString::number(rssiValues[9]));
/*
        switch (test) {
        case 0:
        {
            random_location = "b1";
            break;
        }
        case 1: random_location = "b1";
            break;
        case 2: random_location = "b1";
            break;
        case 3: random_location = "b1";
            break;
        case 4: random_location = "b1";
            break;
        case 5: random_location = "b1";
            break;
        case 6: random_location = "b1";
            break;
        case 7: random_location = "b1";
            break;
        case 8: random_location = "b1";
            break;
        case 9: random_location = "b1";
            break;
        }

*/
        //1 b1 team1 win

        //0 b2 team0 win

        //TEams and locations
        //1 b2
        //0 b1
        qDebug() << "Lcoation :";
        qDebug() << random_location;
        Player * player = game->return_player_id_based(id);
        qDebug() << "Player id :";
        qDebug() << player->getTeam();

        if(random_location == "b1" && player->getTeam() == 1 && player->return_life() == false){
            QDialog dialog;
            ui->listWidget_2->addItem(player->getPlayerName()+" in opponent base game will END");
            dialog.setWindowTitle("GAME END!!");

            QLabel *label = new QLabel("TEAM 1 wins!");
            label->setAlignment(Qt::AlignCenter);
            QFont font = label->font();
            font.setPointSize(14);
            font.setBold(true);
            label->setFont(font);

            QPushButton *button = new QPushButton("Close");
            QObject::connect(button, &QPushButton::clicked, &dialog, &QDialog::accept);

            QVBoxLayout *layout = new QVBoxLayout();
            layout->addWidget(label);
            layout->addWidget(button);
            dialog.setLayout(layout);

            layout->setSpacing(10);
            layout->setAlignment(Qt::AlignCenter);
            dialog.exec();
            QJsonObject end_game;
            end_game["status"] = "game_end";
            QJsonDocument doc(end_game);
            QString jsonString = doc.toJson();
            qDebug() << jsonString;
            game->set_game_start(false);
            emit sendToAllClients(jsonString);

        }
        else if(random_location == "b2" && player->getTeam() == 0 && player->return_life() == false){
            QDialog dialog;
            ui->listWidget_2->addItem(player->getPlayerName()+" in opponent base game will END");
            dialog.setWindowTitle("GAME END!!");
            QLabel *label = new QLabel("TEAM 0 wins!");
            label->setAlignment(Qt::AlignCenter);
            QFont font = label->font();
            font.setPointSize(14);
            font.setBold(true);
            label->setFont(font);

            QPushButton *button = new QPushButton("Close");
            QObject::connect(button, &QPushButton::clicked, &dialog, &QDialog::accept);

            QVBoxLayout *layout = new QVBoxLayout();
            layout->addWidget(label);
            layout->addWidget(button);
            dialog.setLayout(layout);
            layout->setSpacing(10);
            layout->setAlignment(Qt::AlignCenter);

            dialog.exec();
            QJsonObject end_game;
            end_game["status"] = "game_end";
            QJsonDocument doc(end_game);
            QString jsonString = doc.toJson();
            qDebug() << jsonString;
            game->set_game_start(false);
            emit sendToAllClients(jsonString);

        }
        if(random_location == "b1" && player->getTeam() == 0){
            if(player->return_life()){
                ui->listWidget_2->addItem(player->getPlayerName().toUpper()+" will revive in base");
            }

            player->revive();
            int rowCount = ui->playerTable->rowCount();
            int colCount = ui->playerTable->columnCount();

            for (int row = 0; row < rowCount; ++row) {
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = ui->playerTable->item(row, 5);
                    if (item->text() == player->player_id())  {
                        QTableWidgetItem *health = ui->playerTable->item(row,4);
                        health->setText(QString::number(4));
                    }
                }
            }
            QProgressBar* progressBar = progressBarMap[id];
            int currrent=100;
            progressBar->setValue(currrent);
            QJsonObject can_artir;
            can_artir["status"] = "revive";
            can_artir["to"] = id;
            QJsonDocument doc(can_artir);
            QString jsonString = doc.toJson();
            qDebug() << jsonString;
            emit sendToAllClients(jsonString);
        }
        else if(random_location == "b2" && player->getTeam() == 1){
            if(player->return_life()){
                ui->listWidget_2->addItem(player->getPlayerName()+" will revive in base");
            }

            player->revive();
            int rowCount = ui->playerTable->rowCount();
            int colCount = ui->playerTable->columnCount();

            for (int row = 0; row < rowCount; ++row) {
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = ui->playerTable->item(row, 5);
                    if (item->text() == player->player_id())  {
                        QTableWidgetItem *health = ui->playerTable->item(row,4);
                        health->setText(QString::number(4));
                    }
                }
            }
            QProgressBar* progressBar = progressBarMap[id];
            int currrent=100;
            progressBar->setValue(currrent);
            QJsonObject can_artir;
            can_artir["status"] = "revive";
            can_artir["to"] = id;
            QJsonDocument doc(can_artir);
            QString jsonString = doc.toJson();
            qDebug() << jsonString;
            emit sendToAllClients(jsonString);
        }
        if(random_location !=""){
            QJsonObject obj;
            obj["type"] = "set_player_location";
            obj["id"] = id;
            obj["chunk"] =random_location;
            QJsonDocument doc(obj);
            QString jsonString = doc.toJson();
            qDebug() << jsonString;
            emit sendToAllClients(jsonString);
        }


    } else {
        qDebug() << "Invalid or missing RSSI array";
    }
}
void MainWindow::create_player(QJsonObject message){
    ui->pushButton->setDisabled(true);
    QJsonObject new_obj;
    new_obj["name"]= message["userName"];
    new_obj["team"]= message["teamId"];
    Player * new_player = game->create_player(new_obj);

    if(new_player != nullptr){
        QProgressBar* progressBar = nullptr;
        QString id = new_player->player_id();
        QJsonObject id_send;
        id_send["type"] = "create";
        id_send["id"] = id;
        QJsonDocument doc(id_send);
        QString jsonString = doc.toJson();

        //should be specific client
       // emit sendToAllClients(jsonString);0

        QJsonObject send_to_map;
        send_to_map["type"] = "create";
        send_to_map["name"] = new_player->getPlayerName();
        send_to_map["id"] = new_player->player_id();
        send_to_map["team"] =QString::number(new_player->getTeam());

        QJsonDocument doc2(send_to_map);
        QString jsonString_map = doc2.toJson();

        emit sendToAllClients(jsonString_map);

        if(ui->label_5->text() == "TextLabel"){
            progressBar = ui->progressBar;
            ui->label_5->setText(new_player->getPlayerName());
            ui->progressBar->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #2196F3, stop: 1 #90CAF9);" // Optional, to set chunk size
                                               "}");
            }
            else{
                ui->progressBar->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #F44336, stop: 1 #FFCDD2);" // Optional, to set chunk size
                                               "}");
            }

        }
        else if(ui->label_6->text() == "TextLabel"){
            progressBar = ui->progressBar_2;
            ui->label_6->setText(new_player->getPlayerName());
            ui->progressBar_2->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar_2->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #2196F3, stop: 1 #90CAF9);" // Optional, to set chunk size
                                               "}");
            }
            else{
                ui->progressBar_2->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #F44336, stop: 1 #FFCDD2);" // Optional, to set chunk size
                                               "}");
            }
        }

        else if(ui->label_7->text() == "TextLabel"){
            progressBar = ui->progressBar_3;
            ui->label_7->setText(new_player->getPlayerName());
            ui->progressBar_3->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar_3->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #2196F3, stop: 1 #90CAF9);" // Optional, to set chunk size
                                               "}");
            }
            else{
                ui->progressBar_3->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #F44336, stop: 1 #FFCDD2);" // Optional, to set chunk size
                                               "}");
            }
        }

        else if(ui->label_8->text() == "TextLabel"){
            progressBar = ui->progressBar_4;
            ui->label_8->setText(new_player->getPlayerName());
            ui->progressBar_4->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar_4->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #2196F3, stop: 1 #90CAF9);" // Optional, to set chunk size
                                               "}");
            }
            else{
                ui->progressBar_4->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid #B0BEC5;"
                                               "    border-radius: 8px;"
                                               "    background-color: #ECEFF1;"
                                               "    height: 18px;"
                                               "    text-align: center; /* Center the text */"
                                               "font: bold 12px 'Arial'; /* Bold and slightly larger font */"
                                               "color: #000000; /* Text color */"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    border-radius: 7px;"  // Blue color
                                               "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #F44336, stop: 1 #FFCDD2);" // Optional, to set chunk size
                                               "}");
            }
        }

        ui->listWidget_2->clear();
        Player** player = game->returnPlayers();
        int count = game->returnPlayerCount();
        for (int i = 0; i < count; ++i) {
            QTableWidgetItem *nameItem = new QTableWidgetItem(player[i]->getPlayerName());
            QTableWidgetItem *healthItem = new QTableWidgetItem(QString::number(player[i]->get_health()));
            //QTableWidgetItem *teamItem = new QTableWidgetItem(QString::number(player[i]->getTeam()));
            QTableWidgetItem *killItem = new QTableWidgetItem(QString::number(player[i]->return_kill_c()));
            QTableWidgetItem *deathItem = new QTableWidgetItem(QString::number(player[i]->return_death_c()));
            QTableWidgetItem *iditem = new QTableWidgetItem(player[i]->returnPlayerID());

            QString teamName = player[i]->getTeam() == 0 ? "BLUE" : "RED";
            QTableWidgetItem *teamItem = new QTableWidgetItem(teamName);

            if (player[i]->getTeam() == 0) {
                // Team 0, set text color to blue
                teamItem->setBackground(Qt::blue);
            } else if (player[i]->getTeam() == 1) {
                // Team 1, set text color to red
                teamItem->setBackground(Qt::red);
            }
            // Set the items in the table
            ui->playerTable->setItem(i, 0, nameItem);
            ui->playerTable->setItem(i, 1, deathItem);
            ui->playerTable->setItem(i, 2, killItem);
            ui->playerTable->setItem(i, 3, teamItem);
            ui->playerTable->setItem(i, 4, healthItem);
            ui->playerTable->setItem(i, 5, iditem);
        }



        counter++;
        if (progressBar != nullptr) {
            progressBar->setValue(100);
            progressBarMap[new_player->player_id()] = progressBar;
        }
    }
    else{
        emit sendToAllClients("-1");
    }
    ui->port_label_2->setText(QString::number(game->returnPlayerCount()));

    if(game->returnPlayerCount()==4){
        ui->pushButton->setDisabled(false);
    }
    else{
        ui->pushButton->setDisabled(true);
    }
}
void MainWindow::hit_player(QJsonDocument document){
    QJsonObject obj = document.object();
    if (!document.isNull() && document.isObject()) {
        Player* player=game->return_player_id_based(obj["to"].toString());
        Player* from_player = game->return_player_id_based(obj["from"].toString());
        if((player->get_health() == 1 || player->return_life() == true ) && from_player->return_life() == false && player != from_player ){
            if(player->get_health()==1){
                game->return_player_id_based(obj["to"].toString())->increment_death();
                game->return_player_id_based(obj["from"].toString())->increment_kill();
            }

            player->being_hit();
            QJsonObject hit_send;
            hit_send["type"] = "being_hit";
            hit_send["status"] = "dead";
            hit_send["from"] = obj["from"].toString();
            hit_send["to"] = obj["to"].toString();

            //Player* player_that_hits=game->return_player_id_based(obj["from"].toString());

            hit_send["from_death_count"] = game->return_player_id_based(obj["from"].toString())->return_death_c();
            hit_send["from_kill_count"]= game->return_player_id_based(obj["from"].toString())->return_kill_c();
            hit_send["to_death_count"] = game->return_player_id_based(obj["to"].toString())->return_death_c();
            hit_send["to_kill_count"] = game->return_player_id_based(obj["to"].toString())->return_kill_c();

            QJsonDocument doc(hit_send);
            QString jsonString = doc.toJson();
            emit sendToAllClients(jsonString);
            int rowCount = ui->playerTable->rowCount();
            int colCount = ui->playerTable->columnCount();

            for (int row = 0; row < rowCount; ++row) {
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = ui->playerTable->item(row, 5);
                    if (item->text() == game->return_player_id_based(obj["to"].toString() )->player_id())  {
                        QTableWidgetItem *death_item = ui->playerTable->item(row,1);
                        death_item->setText(QString::number(game->return_player_id_based(obj["to"].toString())->return_death_c()));
                        QTableWidgetItem *decrement_health = ui->playerTable->item(row,4);
                        decrement_health->setText(QString::number(game->return_player_id_based(obj["to"].toString())->get_health()));
                    }
                    else if(item->text() == game->return_player_id_based(obj["from"].toString() )->player_id()){
                        QTableWidgetItem *kill_item = ui->playerTable->item(row,2);
                        kill_item->setText(QString::number(game->return_player_id_based(obj["from"].toString())->return_kill_c()));
                    }
                }
            }

            ui->listWidget_2->addItem(game->return_player_id_based(obj["from"].toString())->getPlayerName().toUpper()+"-"
                                      +" STUNNED "+game->return_player_id_based(obj["to"].toString())->getPlayerName().toUpper());
            qDebug() << "Hit Data:" << jsonString;
            QString playerId = obj["to"].toString();
            QProgressBar* progressBar = progressBarMap[playerId];
            int currrent=progressBar->value();
            progressBar->setValue(currrent-25);
        }
        else if(from_player->return_life() == false && player != from_player){
            player->being_hit();
            QJsonObject hit_send;
            //game->return_player_id_based(obj["from"].toString())->increment_kill();
            //game->return_player_id_based(obj["to"].toString())->increment_death();
            hit_send["type"] = "being_hit";
            hit_send["status"] = "hit";
            hit_send["from"] = obj["from"].toString();
            hit_send["to"] = obj["to"].toString();
            hit_send["to_health"] = player->get_health();
            QJsonDocument doc(hit_send);
            QString jsonString = doc.toJson();
            emit sendToAllClients(jsonString);
            int rowCount = ui->playerTable->rowCount();
            int colCount = ui->playerTable->columnCount();

            for (int row = 0; row < rowCount; ++row) {
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = ui->playerTable->item(row, 5);
                    if (item->text() == game->return_player_id_based(obj["to"].toString() )->player_id())  {
                        QTableWidgetItem *decrement_health = ui->playerTable->item(row,4);
                        decrement_health->setText(QString::number(game->return_player_id_based(obj["to"].toString())->get_health()));
                    }
                }
            }

            ui->listWidget_2->addItem(game->return_player_id_based(obj["from"].toString())->getPlayerName().toUpper()+"-"
                                      +" TAGS "+game->return_player_id_based(obj["to"].toString())->getPlayerName().toUpper());
            qDebug() << "Hit Data:" << jsonString;

            QString playerId = obj["to"].toString();
            QProgressBar* progressBar = progressBarMap[playerId];
            int currrent=progressBar->value();
            progressBar->setValue(currrent-25);
        }

    }
    else {
        qDebug() << "Failed to create JSON doc.";
    }
}
void MainWindow::sendAllClientSlot(){
    QString textContent = ui->plainTextEdit->toPlainText();
    emit sendToAllClients(textContent);
}

void MainWindow::on_pushButton_2_clicked()
{
    sendAllClientSlot();
}


void MainWindow::on_pushButton_clicked()
{
    //game = new Game();
    if(!game->returnGameStartorNot()){
        game->set_game_start(true);
        QJsonObject obj;
        obj["type"]="game_start";
        //obj["status"]="start";
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson();
        emit sendToAllClients(jsonString);
        ui->server_check_box_2->setChecked(true);
    }
    else{
        game->set_game_start(false);
        ui->server_check_box_2->setChecked(false);
        QJsonObject obj;
        obj["type"]="game_end";
        //obj["status"]="stopped";
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson();
        emit sendToAllClients(jsonString);
    }
}




void MainWindow::on_pushButton_3_clicked()
{
    //just for test
    ui->listWidget_2->clear();
    QJsonObject obj;
    obj["type"] = "create";
    obj["name"] = "arda";
    obj["id"] = QString::number(counter);
    obj["team"] =QString::number(team_set);

    Player * new_player = game->create_player(obj);
    //qDebug() << "Player team:" << new_player->getTeam();
    //return id to client
    if(new_player != nullptr){
        QProgressBar* progressBar = nullptr;
        QString id = new_player->player_id();
        QJsonObject id_send;
        id_send["type"] = "create";
        id_send["id"] = id;
        QJsonDocument doc(id_send);
        QString jsonString = doc.toJson();

        //should be specific client
        //emit sendToAllClients(jsonString);

        QJsonObject send_to_map;
        send_to_map["type"] = "create";
        send_to_map["name"] = new_player->getPlayerName();
        send_to_map["id"] = new_player->player_id();
        send_to_map["team"] =QString::number(new_player->getTeam());
        qDebug() << "Send data:" << send_to_map;
        QJsonDocument doc2(send_to_map);
        QString jsonString_map = doc2.toJson();
        qDebug() << "Send data:" << jsonString_map;
        emit sendToAllClients(jsonString_map);

        if(ui->label_5->text() == "TextLabel"){
            progressBar = ui->progressBar;
            ui->label_5->setText(new_player->getPlayerName());
            ui->progressBar->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid grey;"
                                               "    border-radius: 5px;"
                                               "    background-color: #FFFFFF;"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    background-color: #05B8CC;"  // Blue color
                                               "    width: 20px;" // Optional, to set chunk size
                                               "}");
            }
            else{
                ui->progressBar->setStyleSheet("QProgressBar {"
                                               "    border: 2px solid grey;"
                                               "    border-radius: 5px;"
                                               "    background-color: blue;"
                                               "}"
                                               "QProgressBar::chunk {"
                                               "    background-color: #05B8CC;"  // Blue color
                                               "    width: 20px;" // Optional, to set chunk size
                                               "}");
            }

        }
        else if(ui->label_6->text() == "TextLabel"){
            progressBar = ui->progressBar_2;
            ui->label_6->setText(new_player->getPlayerName());
            ui->progressBar_2->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar_2->setStyleSheet("QProgressBar {"
                                                 "    border: 2px solid grey;"
                                                 "    border-radius: 5px;"
                                                 "    background-color: #FFFFFF;"
                                                 "}"
                                                 "QProgressBar::chunk {"
                                                 "    background-color: #05B8CC;"  // Blue color
                                                 "    width: 20px;" // Optional, to set chunk size
                                                 "}");
            }
            else{
                ui->progressBar_2->setStyleSheet("QProgressBar {"
                                                 "    border: 2px solid grey;"
                                                 "    border-radius: 5px;"
                                                 "    background-color: blue;"
                                                 "}"
                                                 "QProgressBar::chunk {"
                                                 "    background-color: #05B8CC;"  // Blue color
                                                 "    width: 20px;" // Optional, to set chunk size
                                                 "}");
            }
        }

        else if(ui->label_7->text() == "TextLabel"){
            progressBar = ui->progressBar_3;
            ui->label_7->setText(new_player->getPlayerName());
            ui->progressBar_3->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar_3->setStyleSheet("QProgressBar {"
                                                 "    border: 2px solid grey;"
                                                 "    border-radius: 5px;"
                                                 "    background-color: #FFFFFF;"
                                                 "}"
                                                 "QProgressBar::chunk {"
                                                 "    background-color: #05B8CC;"  // Blue color
                                                 "    width: 20px;" // Optional, to set chunk size
                                                 "}");
            }
            else{
                ui->progressBar_3->setStyleSheet("QProgressBar {"
                                                 "    border: 2px solid grey;"
                                                 "    border-radius: 5px;"
                                                 "    background-color: blue;"
                                                 "}"
                                                 "QProgressBar::chunk {"
                                                 "    background-color: #05B8CC;"  // Blue color
                                                 "    width: 20px;" // Optional, to set chunk size
                                                 "}");
            }
        }

        else if(ui->label_8->text() == "TextLabel"){
            progressBar = ui->progressBar_4;
            ui->label_8->setText(new_player->getPlayerName());
            ui->progressBar_4->setValue(100);
            if(new_player->getTeam() == 0){
                ui->progressBar_4->setStyleSheet("QProgressBar {"
                                                 "    border: 2px solid grey;"
                                                 "    border-radius: 5px;"
                                                 "    background-color: #FFFFFF;"
                                                 "}"
                                                 "QProgressBar::chunk {"
                                                 "    background-color: #05B8CC;"  // Blue color
                                                 "    width: 20px;" // Optional, to set chunk size
                                                 "}");
            }
            else{
                ui->progressBar_4->setStyleSheet("QProgressBar {"
                                                 "    border: 2px solid grey;"
                                                 "    border-radius: 5px;"
                                                 "    background-color: blue;"
                                                 "}"
                                                 "QProgressBar::chunk {"
                                                 "    background-color: #05B8CC;"  // Blue color
                                                 "    width: 20px;" // Optional, to set chunk size
                                                 "}");
            }
        }

        //Display player in ui
        ui->listWidget_2->clear();
        Player** player = game->returnPlayers();
        int count = game->returnPlayerCount();
        for(int i = 0; i < count; i++) {
            ui->listWidget_2->addItem("Player: " + player[i]->getPlayerName() +
                                      " Id: " + player[i]->player_id() +
                                      " Team: " + QString::number(player[i]->getTeam()));

            QTableWidgetItem *nameItem = new QTableWidgetItem(player[i]->getPlayerName());
            QTableWidgetItem *healthItem = new QTableWidgetItem(QString::number(player[i]->get_health()));
            //QTableWidgetItem *teamItem = new QTableWidgetItem(QString::number(player[i]->getTeam()));
            //kill & death
            QTableWidgetItem *killItem = new QTableWidgetItem(QString::number(player[i]->return_kill_c()));
            QTableWidgetItem *deathItem = new QTableWidgetItem(QString::number(player[i]->return_death_c()));
            QTableWidgetItem *iditem = new QTableWidgetItem(player[i]->returnPlayerID());

            QString teamName = player[i]->getTeam() == 0 ? "Blue" : "Red";
            QTableWidgetItem *teamItem = new QTableWidgetItem(teamName);


            // Add items to the table
            ui->playerTable->setItem(i, 0, nameItem);
            ui->playerTable->setItem(i, 1, deathItem);
            ui->playerTable->setItem(i, 2, killItem);
            ui->playerTable->setItem(i, 3, teamItem);
            ui->playerTable->setItem(i, 4, healthItem);
            ui->playerTable->setItem(i,5,iditem);
        }
        counter++;
        if (progressBar != nullptr) {
            progressBar->setValue(100);
            progressBarMap[new_player->player_id()] = progressBar;
        }
    }
    else{
        emit sendToAllClients("-1");
    }
    ui->port_label_2->setText(QString::number(game->returnPlayerCount()));

    if(game->returnPlayerCount()==4){
        ui->pushButton->setDisabled(false);
        ui->server_check_box_2->setDisabled(true);
    }
    else{
        ui->pushButton->setDisabled(true);
    }
    if(team_set==1){
        team_set--;
    }
    else{
        team_set++;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QString random_location[10];
    random_location[0]="b1";
    random_location[1]="b2";
    random_location[2]="a1";
    random_location[3]="a2";
    random_location[4]="a3";
    random_location[5]="a4";
    random_location[6]="a5";
    random_location[7]="a6";
    random_location[8]="a7";
    random_location[9]="a8";
    //random_location[0]="b1";

    int randomValue = QRandomGenerator::global()->bounded(4);
    int randomValueArray = QRandomGenerator::global()->bounded(10);

    QJsonObject obj;
    obj["type"] = "set_player_location";
    obj["id"] = QString::number(randomValue);
    obj["chunk"] =random_location[randomValueArray];
    QJsonDocument doc(obj);
    QString jsonString = doc.toJson();
    qDebug() << jsonString;
    emit sendToAllClients(jsonString);
}


void MainWindow::on_pushButton_5_clicked()
{
    if(game->returnGameStartorNot()){
        int randomNumber = QRandomGenerator::global()->bounded(4);
        QString playerId = QString::number(randomNumber);
        QProgressBar* progressBar = progressBarMap[playerId];
        int currrent=progressBar->value();
        progressBar->setValue(currrent-25);
    }

}


void MainWindow::on_pushButton_6_clicked()
{
	QProcess *process = new QProcess(this);
	process->start("/usr/lib/Linux/cubukdeneme2.sh");
}


void MainWindow::on_pushButton_7_clicked()
{
    if(game->returnGameStartorNot()){
        int randomNumber = QRandomGenerator::global()->bounded(4);
        QString playerId = QString::number(randomNumber);
        QProgressBar* progressBar = progressBarMap[playerId];
        progressBar->setValue(100);
        game->return_player_id_based(playerId)->revive();
    }

}


void MainWindow::on_pushButton_8_clicked()
{
    Classifier classifier1;
    float arr[3] = {-30,-45,-20};

    int test = classifier1.predict(arr);
    ui->listWidget->addItem(QString::number(test));
}


