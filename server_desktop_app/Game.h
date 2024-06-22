#ifndef GAME_H
#define GAME_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include "Player.h"
class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    int player_count=0;
    int team1_count=0;
    int team2_count=0;
    void set_game_start(bool start_or_not){
        game_started=start_or_not;
    }
    bool returnGameStartorNot(){
        return game_started;
    }
    void send_players_for_start_info(){
        for(int i=0;i<4;i++){
            player[i]->set_game_start(true);
        }
    }
    Player* create_player(QJsonObject message) {
        if (player_count < 4) {
            QJsonValue value = message["team"];
            qDebug() << "Team (raw JSON):" << value.toString();
            QString teamStr = value.toString().trimmed();
            qDebug() << "Team (QString):" << teamStr;

            bool ok;
            int teamNumber = teamStr.toInt(&ok);
            if((teamNumber==0 && team1_count>=2) || (teamNumber==1 && team2_count>=2) ){
                return nullptr;
            }
            if(teamNumber==0){
                team1_count++;
            }
            else if(teamNumber==1){
                team2_count++;
            }
            if (!ok) {
                qWarning() << "Failed to convert team number from string to int.";
                return nullptr;
            }

            qDebug() << "Team (int):" << teamNumber;
            player[player_count] = new Player(
                message["name"].toString(),
                QString::number(player_count),
                4,
                teamNumber
                );

            Player* createdPlayer = player[player_count];
            ++player_count;
            return createdPlayer;
        }
        return nullptr;
    }

    Player** returnPlayers (){
        return player;
    }
    int returnPlayerCount(){
        return player_count;
    }
    Player* get_test_player(int id){
        return player[id];
    }
    Player* return_player_id_based(QString id){
        for(int i=0;i<returnPlayerCount();i++){
            if(player[i]->player_id() == id){
                return player[i];
            }
        }
        return nullptr;
    }
private:
    Player *player[4];
    bool game_started =false;
signals:
};

#endif // GAME_H
