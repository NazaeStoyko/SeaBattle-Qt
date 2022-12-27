#include "player.h"




Player::Player(QString nick, int age, int id)
{
    this->id = id;
    this->nick = nick;
    this->age = age;
}

void Player::setId(int id)
{
    this->id = id;
}

void Player::setNick(QString nick)
{
    this->nick = nick;
}

QString Player::getNick()
{
    return nick;
}

void Player::setAge( int age)
{
    this->age = age;

}
int Player::getAge ()
{
    return age;
}
