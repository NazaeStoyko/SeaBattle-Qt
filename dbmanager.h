#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDatabase>
#include <QVariantList>
#include "player.h"
class DBManager
{
public:
    DBManager();

    /* Методи для безпоCередньої роботи з клаCом
     * Підключення до бази даних і вCтавка запиCів у таблицю
     * */
    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool inserIntoTable(Player& player) = 0;



};

#endif // DBMANAGER_H
