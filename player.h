#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{
    int id;
    QString nick;
    int  age;

public:
    Player(QString nick, int  age, int id = 0);
    void setId(int id);
    void setNick(QString nick);
    QString getNick();
    void setAge( int age);
    int getAge ();
};

#endif // PLAYER_H
