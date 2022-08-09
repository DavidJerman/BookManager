#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool loginDataPresent();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeStatus(const std::string &message);

    void disableWindows();
    void enableWindows();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::MainWindow *ui;
    QString status;
    bool loggedIn;
};
#endif // MAINWINDOW_H
