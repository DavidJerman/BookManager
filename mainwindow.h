#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlTableModel>
#include "author.h"
#include "publisher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool loginDataPresent();

    void changeWindowsState(bool state);

    bool bookDataPresent();

    bool authorDataPresent();

    bool publisherDataPresent();

    void loadAuthorsData();

    void loadPublishersData();

    void setBookModelToTable();

    void setAuthorModelToTable();

    void setPublisherModelToTable();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeStatus(const std::string &message);

    void disableWindows();
    void enableWindows();

private slots:
    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_AddBookButton_clicked();

    void on_AddAuthorButton_clicked();

    void on_AddPublisherButton_clicked();

    void on_BooksDisplayGrid_clicked(const QModelIndex &index);

    void on_AuthorsDisplayGrid_clicked(const QModelIndex &index);

    void on_PublisherDisplayGrid_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QString status;
};
#endif // MAINWINDOW_H
