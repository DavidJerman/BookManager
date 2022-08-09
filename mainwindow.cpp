#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loggedIn = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatus(const std::string &message) {
    this->status = QString::fromStdString(message);
    ui->Status->setText(this->status);
}

void MainWindow::on_LoginButton_clicked()
{
    if (!loginDataPresent()) {
        ui->LastAction->setText("Missing login information!");
    } else {
        auto m = Database::login(ui->UsernameFrom->text().toStdString(), ui->PasswordForm->text().toStdString());
        ui->LastAction->setText(QString::fromStdString(m.getMessage()));
    }
}

bool MainWindow::loginDataPresent() {
    return !(ui->UsernameFrom->text().begin() == ui->UsernameFrom->text().end())
            && !(ui->PasswordForm->text().begin() == ui->PasswordForm->text().end());
}

void MainWindow::disableWindows() {

}

void MainWindow::enableWindows() {

}
