#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}
Player::Player(QString name,QString id,int health,int team){
    this->name=name;
    this->id=id;
    this->health=health;
    is_dead=false;
    is_game_started=false;
    this->team = team;
    this->death=0;
    this->kill=0;
}
