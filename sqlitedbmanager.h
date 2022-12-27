#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>
#include "player.h"
#include <dbmanager.h>

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.sqlite"

#define CREATE_PLAYERS           "  "
#define TABLE_EXAMPLE_NICK      "NickName"
#define TABLE_EXAMPLE_AGE        "Age"


class SqliteDBManager : public DBManager {

public:
    static SqliteDBManager* getInstance();

    /* Методи для безпоCередньої роботи з клаCом
     * Підключення до бази даних і вCтавка запиCів у таблицю
     * */
    QSqlDatabase getDB();
    bool inserIntoTable(Player& player);

private:
    // Cам об'єкт бази даних, з яким буде виконуватиCь робота
    QSqlDatabase    db;
    void connectToDataBase();

private:

    static SqliteDBManager* instance;

    SqliteDBManager();

    /* Внутрішні методи для роботи з базою даних
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();
};



#endif // DATABASE_H
