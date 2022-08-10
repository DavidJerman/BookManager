#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <string>

#include "message.h"
#include "book.h"

class Database
{
private:
    static QSqlDatabase db;

public:

    Database() = default;
    ~Database() = default;

    static bool connect(const QString &connector, const QString &hostname, int port,
                 const QString &dbName, const QString &username,
                 const QString &password);
    static bool checkConnection();

    static Message login(const std::string username, const std::string passowrd);

    static Message _register(const std::string username, const std::string password);

    static bool validPassword(const std::string &password);

    static bool validUsername(const std::string &username);

    static Message addBook(const Book &book);
};

#endif // DATABASE_H
