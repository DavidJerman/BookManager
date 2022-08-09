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
    query.exec(QString::fromStdString("SELECT password_hash FROM credential WHERE username = '" + username + "'"));

    if (query.next()) {
        auto pass = query.value(0).toString();

        QSqlQuery md5Q(QString::fromStdString("SELECT SHA2('" + password + "', 256);"));
        md5Q.exec();

        if (!md5Q.next()) return {0, "MD5 query error!"};
        else if (pass.compare(md5Q.value(0).toString())) return {0, "Password does not match the given username!"};
        else {
            query.exec(QString::fromStdString("UPDATE credential SET last_access = NOW() WHERE username ="
                                              "'" + username + "';"));
            return {1, "Welcome, " + username + "!"};
        }
    }
    else return {0, "User not found!"};
}

Message Database::_register(const std::string username, const std::string password) {

    if (!checkConnection()) return {0, "Connection is not active!"};

    if (!validUsername(username)) return {0, "Username not valid, must be at least 5 character long!"};

    if (!validPassword(password)) return {0, "Password must contain numbers, upper/lowercase letters and special characters!"};

    QSqlQuery query (db);
    query.exec(QString::fromStdString("SELECT username FROM credential WHERE username = '" + username + "'"));

    if (!query.next()) {
        query.exec(QString::fromStdString("INSERT INTO credential VALUES ("
                                          "null, '" + username + "', SHA2('" + password
                                          + "', 256), NOW())"));
        return {1, "User created, please login!"};
    }
    else return {0, "User already exists!!"};
}

bool Database::validPassword(const std::string &password) {
    if (password.length() < 8) return false;
    bool lowerCase = false, upperCase = false, digit = false, special = false;
    for (const auto &c: password) {
        if (std::islower(c)) lowerCase = true;
        else if (std::isupper(c)) upperCase = true;
        else if (std::isdigit(c)) digit = true;
        else special = true;
    }
    return lowerCase & upperCase & digit & special;
}

bool Database::validUsername(const std::string &username) {
    return username.length() > 4;
}

bool Database::validBook(const Book &book) {

    QSqlQuery query (db);

    // We are just looking for a unique ISBN, title, author and publisher
    // TODO
    query.exec(QString::fromStdString("SELECT title, isbn FROM book WHERE title"));
}
