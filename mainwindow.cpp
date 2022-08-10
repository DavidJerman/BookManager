#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loggedIn = false;
    disableWindows();
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
        if (m.getStatus() == 1) {
            enableWindows();
            ui->UsernameFrom->clear();
            ui->PasswordForm->clear();
        }
    }
}

bool MainWindow::loginDataPresent() {
    return !(ui->UsernameFrom->text().begin() == ui->UsernameFrom->text().end())
            && !(ui->PasswordForm->text().begin() == ui->PasswordForm->text().end());
}

void MainWindow::changeWindowsState(bool state) {
    ui->TabWidget->setEnabled(state);

    // Books tab
    ui->TitleLineEdit->setEnabled(state);
    ui->SynopsisTextEdit->setEnabled(state);
    ui->ISBNLineEdit->setEnabled(state);
    ui->YearSpinBox->setEnabled(state);
    ui->RatingSpinBox->setEnabled(state);
    ui->AuthorComboBox->setEnabled(state);
    ui->PublisherLabel->setEnabled(state);
    ui->AddBookButton->setEnabled(state);

    // Authors tab
    ui->AuthorNameLineEdit->setEnabled(state);
    ui->AuthorDateEdit->setEnabled(state);
    ui->BiographyTextEdit->setEnabled(state);
    ui->AddAuthorButton->setEnabled(state);

    // Publishers tab
    ui->PublisherNameLineEdit->setEnabled(state);
    ui->TaxIDLineEdit->setEnabled(state);
    ui->AddPublisherButton->setEnabled(state);
}

void MainWindow::disableWindows() {
    changeWindowsState(false);
}

void MainWindow::enableWindows() {
    changeWindowsState(true);
}

void MainWindow::on_RegisterButton_clicked()
{
    if (!loginDataPresent()) {
        ui->LastAction->setText("Missing login information!");
    } else {
        auto m = Database::_register(ui->UsernameFrom->text().toStdString(), ui->PasswordForm->text().toStdString());
        ui->LastAction->setText(QString::fromStdString(m.getMessage()));
        ui->UsernameFrom->clear();
        ui->PasswordForm->clear();
    }
}

bool MainWindow::bookDataPresent() {
    return !(ui->TitleLineEdit->text().begin() == ui->TitleLineEdit->text().end()
             || ui->SynopsisTextEdit->toPlainText().begin() == ui->SynopsisTextEdit->toPlainText().end()
             || ui->ISBNLineEdit->text().begin() == ui->ISBNLineEdit->text().end()
             || ui->AuthorComboBox->currentIndex() == -1
             || ui->PublisherComboBox->currentIndex() == -1);
}

void MainWindow::on_AddBookButton_clicked()
{
    if (!bookDataPresent()) {
        ui->LastAction->setText("Missing book information!");
    } else {
        Book b (ui->TitleLineEdit->text().toStdString(),
                ui->SynopsisTextEdit->toPlainText().toStdString(),
                ui->ISBNLineEdit->text().toStdString(),
                ui->YearSpinBox->value(),
                ui->RatingSpinBox->value(),
                std::atoi(ui->AuthorComboBox->currentText().toStdString().c_str()),
                std::atoi(ui->PublisherComboBox->currentText().toStdString().c_str()));
        auto m = Database::addBook(b);
        ui->LastAction->setText(QString::fromStdString(m.getMessage()));
        if (m.getStatus() == 1) {
            ui->TitleLineEdit->clear();
            ui->SynopsisTextEdit->clear();
            ui->ISBNLineEdit->clear();
            ui->YearSpinBox->clear();
            ui->RatingSpinBox->clear();
        }
    }
}
