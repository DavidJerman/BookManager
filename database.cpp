#include "database.h"

QSqlDatabase Database::db = QSqlDatabase();

bool Database::connect(const QString &connector, const QString &hostname, int port,
                  const QString &dbName, const QString &username,
                  const QString &password) {

    db = QSqlDatabase::addDatabase(connector);
    db.setPort(port);
    db.setHostName(hostname);
    db.setDatabaseName(dbName);
    db.setUserName(username);
    db.setPassword(password);

    return true;
}

bool Database::checkConnection() {
    return db.open();
}

Message Database::login(const std::string username, const std::string password) {

    if (!checkConnection()) return {0, "Connection is not active!"};

    QSqlQuery query (db);
    query.exec(QString::fromStdString("SELECT password_hash FROM credentials WHERE username = '" + username + "'"));

    while (query.next()) {
        auto pass = query.value(0).toString();

        QSqlQuery md5Q(QString::fromStdString("SELECT MD5('" + password + "');"));
        md5Q.exec();

        if (!md5Q.next()) return {0, "MD5 query error!"};
        if (pass.compare(md5Q.value(0).toString())) return {0, "Password does not match the given username!"};
        else return {1, "Welcome, " + username + "!"};
    }
    return {0, "User not found!"};
}
