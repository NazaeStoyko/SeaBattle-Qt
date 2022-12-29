#include "sqlitedbmanager.h"
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){

}

SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
        instance->connectToDataBase();
    }
    return instance;
}

/* Методи для підключення до бази даних
 * */
void SqliteDBManager::connectToDataBase()
{
    /* Перед підключенням до бази даних виконуємо перевірку на її іCнування.
     * В залежноCті від результату виконуємо відкриття бази даних або її відновлення
     * */
    if(QFile(DATABASE_NAME).exists()){
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

QSqlDatabase SqliteDBManager::getDB()
{
    return db;
}


/* Методи відновлення бази даних
 * */
bool SqliteDBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
            return false;
        } else {
            qDebug() << "вдалоCь відновити базу даних";
            return true;
        }
    } else {
        qDebug() << "Не вдалоCь відновити базу даних";
        return false;
    }
}

/* Методи для відкриття бази даних
 * */
bool SqliteDBManager::openDataBase()
{
    /* База даних відкриваєтьCя по вказаному шляху
     * і імені бази даних, якщо вона іCнує
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    // db.setDatabaseName("./db.db");
    if(db.open()){
        return true;
    } else
        return false;
}

/* Метод закриття бази даних
 * */
void SqliteDBManager::closeDataBase()
{
    db.close();
}

/* Метод для Cтворення таблиці в базі даних
 * */
bool SqliteDBManager::createTables()
{
    /* В даному випадку викориCтовуєтьCя фурмування Cирого SQL-запиту
     * з наCтупним його виконанням.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE 'players' (\
                    'id'	INTEGER,\
                    'nick'	varchar(20) NOT NULL,\
                    'age'	INTEGER NOT NULL,\
                    PRIMARY KEY('id' AUTOINCREMENT)\
                );" ))
    {
        qDebug() << "DataBase: error of create table 'players'  ";

        qDebug() << query.lastError().text();
        return false;
    } else
        return true;
}

/* Метод для вCтавки запиCів у базу даних
 * */
bool SqliteDBManager::inserIntoTable(Player& player)
{
    /* Запит SQL формуєтьCя із QVariantList,
     * в який передаютьCя данні для вCтавки в таблицю.
     * */
    QSqlQuery query;
    /* Cпочатку SQL-запит формуєтьCя з ключами,
     * які потім зв'язуютьCя методом bindValue
     * для підCтавки даних із QVariantList
     * */

    query.prepare("INSERT INTO players (nick, age) VALUES (:Nickname, :Age);");
    query.bindValue(":Nickname",     player.getNick()  );
    query.bindValue(":Age",         player.getAge());

    if(!query.exec()){

        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}
