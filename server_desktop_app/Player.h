#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    Player(QString name,QString id,int health,int team);
    QString returnPlayerID(){
        return id;
    }
    void being_hit(){
        if(!is_dead && !is_game_started){
            health--;
            if(health==0){
                is_dead=true;
            }
        }
    }
    bool return_life(){
        return is_dead;
    }
    void setTeam(bool team){
        this->team=team;
    }
    void set_game_start(bool start){
        is_game_started=start;
    }
    QString getPlayerName(){
        return name;
    }
    QString player_id(){
        return id;
    }
    int get_health(){
        return health;
    }
    int getTeam(){
        return team;
    }
    QString all_info_about_player(){
        QString numberAsString = QString::number(get_health());
        return player_id()+" "+getPlayerName() +" " + "Health: " + numberAsString;
    }
    void increment_kill(){
        kill++;
    }
    int return_kill_c(){
        return kill;
    }
    void increment_death(){
        death++;
    }
    int return_death_c(){
        return death;
    }
    void revive(){
        is_dead =false;
        health = 4;
    }
private:
    QString name;
    QString id;
    int health;
    bool is_dead;
    bool is_game_started;
    int kill;
    int death;
    int team;
    //location
signals:

};

#endif // PLAYER_H
