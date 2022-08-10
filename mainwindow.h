#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <hash_map>
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

private:
    Ui::MainWindow *ui;
    QString status;
};
#endif // MAINWINDOW_H
