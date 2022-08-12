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

    // This is not really super safe, since anyone can still obtain the password hashes, given he knows
    // the credentials used for accessing this database
    // Will redesign this
    query.exec(QString::fromStdString("SELECT STRCMP(password_hash, SHA2('"
                                      + password
                                      + "', 256)) "
                                      "FROM credential "
                                      "WHERE username = '" + username + "'"));

    if (query.next()) {
        auto res = query.value(0).toString().toStdString();

        if (res[0] != '0') return {0, "Password does not match the given username!"};
        else {
            query.exec(QString::fromStdString("UPDATE credential SET last_access = NOW() WHERE username ="
                                              "'" + username + "';"));
            return {1, "Welcome, " + username + "!"};
        }
    }
    else return {0, "User not found!"};
}

Message Database::_register(const std::string username, const std::string password) {

    // This is just an idea, registering like this is not safe
    if (!checkConnection()) return {0, "Connection is not active!"};

    if (!validUsername(username)) return {0, "Username not valid, must be at least 5 character long!"};

    if (!validPassword(password)) return {0, "Password must contain numbers, upper/lowercase letters and special characters!"};

    QSqlQuery query (db);
    query.exec(QString::fromStdString("SELECT username FROM credential WHERE username = '" + username + "'"));

    if (!query.next()) {
        query.exec(QString::fromStdString("INSERT INTO credential VALUES ("
                                          "null, '" + username + "', SHA2('" + password
                                          + "', 256), NOW())"));
        db.commit();
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

Message Database::addBook(const Book &book) {

    QSqlQuery query (db);

    // We are just looking for a unique ISBN, and existent author and publisher
    query.exec(QString::fromStdString("SELECT isbn FROM book WHERE isbn = '" + book.getISBN() + "';"));
    if (query.next()) return {0, "This ISBN already exists!"};

    query.exec(QString::fromStdString("SELECT ID FROM author WHERE ID = " + std::to_string(book.getAuthor())));
    if (!query.next()) return {0, "Selected author does not exist, please add it!"};

    query.exec(QString::fromStdString("SELECT ID FROM publisher WHERE ID = " + std::to_string(book.getPublisher())));
    if (!query.next()) return {0, "Selected publisher does not exist, please add it!"};

    if (book.getYearOfRelease() < 0 || book.getYearOfRelease() > 2050) return {0, "Invalid year of release!"};

    if (book.getRating() < 1 || book.getRating() > 5) return {0, "Invalid rating!"};

    query.exec(QString::fromStdString("INSERT INTO book VALUES (null, '"
                                      + book.getTitle() + "','"
                                      + book.getSynopsis() + "','"
                                      + book.getISBN() + "',"
                                      + std::to_string(book.getYearOfRelease()) + ","
                                      + std::to_string(book.getRating()) + ","
                                      + std::to_string(book.getAuthor()) + ","
                                      + std::to_string(book.getPublisher()) + ")"));
    db.commit();

    return {1, "Book added successfully!"};
}

Message Database::addAuthor(const Author &author) {

    QSqlQuery query (db);

    // TODO: Warn user about duplicates
    query.exec(QString::fromStdString("INSERT INTO author VALUES (null, '"
                                      + author.getName() + "','"
                                      + author.getBirthDate() + "','"
                                      + author.getBiography() + "')"));
    db.commit();

    return {1, "Author added succesfully!"};
}

Message Database::addPublisher(const Publisher &publisher) {

    QSqlQuery query (db);

    // We are just looking for duplicating tax IDs
    query.exec(QString::fromStdString("SELECT tax_id FROM book WHERE tax_id = '" + publisher.getTaxID() + "';"));
    if (query.next()) return {0, "This publisher's Tax ID already exists!"};

    // TODO: Warn user about duplicates
    query.exec(QString::fromStdString("INSERT INTO publisher VALUES (null, '"
                                      + publisher.getName() + "','"
                                      + publisher.getTaxID() + "')"));
    db.commit();

    return {1, "Publisher added successfully!"};
}

std::vector<Author> Database::getAuthors() {
    std::vector<Author> authorNames;

    QSqlQuery query (db);
    query.exec("SELECT ID, full_name, birth_date, biography  FROM author ORDER BY full_name ASC");

    while (query.next()) authorNames.push_back({query.value(1).toString().toStdString(),
                                                query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                std::atoi(query.value(0).toString().toStdString().c_str())});

    return authorNames;
}

std::vector<Publisher> Database::getPublisherNames() {
    std::vector<Publisher> publisherNames;

    QSqlQuery query (db);
    query.exec("SELECT ID, full_name, tax_id FROM publisher ORDER BY full_name ASC");

    while (query.next()) publisherNames.push_back({query.value(1).toString().toStdString(),
                                                   query.value(2).toString().toStdString(),
                                                   std::atoi(query.value(0).toString().toStdString().c_str())});

    return publisherNames;
}
