#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
            loadAuthorsData();
            loadPublishersData();
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
        auto authorData = ui->AuthorComboBox->itemData(ui->AuthorComboBox->currentIndex()).value<QList<QVariant>>();
        auto publisherData = ui->PublisherComboBox->itemData(ui->PublisherComboBox->currentIndex()).value<QList<QVariant>>();

        auto authorID = authorData.first().toInt();
        auto publisherID = publisherData.first().toInt();

        Book b (ui->TitleLineEdit->text().toStdString(),
                ui->SynopsisTextEdit->toPlainText().toStdString(),
                ui->ISBNLineEdit->text().toStdString(),
                ui->YearSpinBox->value(),
                ui->RatingSpinBox->value(),
                authorID,
                publisherID);
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

bool MainWindow::authorDataPresent() {
    return !(ui->AuthorNameLineEdit->text().begin() == ui->AuthorNameLineEdit->text().end()
             && ui->BiographyTextEdit->toPlainText().begin() == ui->BiographyTextEdit->toPlainText().end());
}


void MainWindow::on_AddAuthorButton_clicked()
{
    if (!authorDataPresent()) {
        ui->LastAction->setText("Missing author information!");
    } else {
        auto date = ui->AuthorDateEdit->text().toStdString();

        std::string year, month, day;
        month = date.substr(0, date.find('/'));
        day = date.substr(date.find('/') + 1, date.find_last_of('/') - date.find('/') - 1);
        year = date.substr(date.find_last_of('/') + 1);
        std::cout << year << "-" << month << "-" << day << std::endl;

        Author a (ui->AuthorNameLineEdit->text().toStdString(),
                  year + "-" + month + "-" + day,
                  ui->BiographyTextEdit->toPlainText().toStdString());
        auto m = Database::addAuthor(a);
        ui->LastAction->setText(QString::fromStdString(m.getMessage()));
        if (m.getStatus() == 1) {
            ui->AuthorNameLineEdit->clear();
            ui->BiographyTextEdit->clear();
            loadAuthorsData();
        }
    }
}

bool MainWindow::publisherDataPresent() {
    return !(ui->PublisherNameLineEdit->text().begin() == ui->PublisherNameLineEdit->text().end()
             && ui->TaxIDLineEdit->text().begin() == ui->TaxIDLineEdit->text().end());
}

void MainWindow::on_AddPublisherButton_clicked()
{
    if (!publisherDataPresent()) {
        ui->LastAction->setText("Missing publisher information!");
    } else {
        Publisher p (ui->PublisherNameLineEdit->text().toStdString(),
                     ui->TaxIDLineEdit->text().toStdString());
        auto m = Database::addPublisher(p);
        ui->LastAction->setText(QString::fromStdString(m.getMessage()));
        if (m.getStatus() == 1) {
            ui->PublisherNameLineEdit->clear();
            ui->TaxIDLineEdit->clear();
            loadPublishersData();
        }
    }
}


void MainWindow::loadAuthorsData() {
    auto authors = Database::getAuthors();
    ui->AuthorComboBox->clear();
    for (const auto &item: authors)
        ui->AuthorComboBox->addItem(item, QList<QVariant>()
                                    << item.getID()
                                    << QString::fromStdString(item.getName())
                                    << QString::fromStdString(item.getBirthDate())
                                    << QString::fromStdString(item.getBiography()));
}

void MainWindow::loadPublishersData() {
    auto publishers = Database::getPublisherNames();
    ui->PublisherComboBox->clear();
    for (const auto &item: publishers)
        ui->PublisherComboBox->addItem(item, QList<QVariant>()
                                       << item.getID()
                                       << QString::fromStdString(item.getName())
                                       << QString::fromStdString(item.getTaxID()));
}
