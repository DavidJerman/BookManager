#include "mainwindow.h"

#include <QApplication>

#include <QSql>
#include <QSqlDatabase>

#include "database.h"

#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include <fstream>


class App {
private:
    std::stringstream ss;
    std::shared_ptr<QApplication> a {nullptr};
    std::shared_ptr<MainWindow> w {nullptr};

public:
    App(int argc, char *argv[]) {
        this->a = std::make_shared<QApplication>(argc, argv);
        this->w = std::make_shared<MainWindow>();

        {
            QString appName = QString::fromStdString("Empty");
            QString windowTitle = QString::fromStdString("Books App");
            this->a->setApplicationDisplayName(appName);
            this->w->setWindowTitle(windowTitle);
        }

        this->w->show();

        ss << "Connecting...";
        w->changeStatus(ss.str());
        ss.str(std::string());

        // You can just hardcode the data if needed
        std::ifstream stream("sqlLoginData");
        std::string connector, hostname, port, dbName, username, password;
        std::getline(stream, connector);
        std::getline(stream, hostname);
        std::getline(stream, port);
        std::getline(stream, dbName);
        std::getline(stream, username);
        std::getline(stream, password);
        Database::connect(QString::fromStdString(connector), QString::fromStdString(hostname), std::atoi(port.c_str()),
                          QString::fromStdString(dbName), QString::fromStdString(username), QString::fromStdString(password));

        ss << "Database connection: " << (Database::checkConnection() ? "success!" : "fail!");
        w->changeStatus(ss.str());
        ss.str(std::string());
    }

    ~App() {}

    auto exec() const {
        return a->exec();
    }
};


int main(int argc, char *argv[]) {
    App app (argc, argv);
    return app.exec();
}
