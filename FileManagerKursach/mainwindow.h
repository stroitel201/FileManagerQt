#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"
#include <QListWidgetItem>
#include <QTableWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_leftGoToButton_clicked();
    void ondrivelistItemClicked(QListWidgetItem* item);
    void on_showHidcheckBox_stateChanged(int arg1);
    void on_filetableItem_Clicked(QTableWidgetItem* item);
     void on_openButton_clicked();



     void on_lefttoolButton_pressed();

     void on_righttoolButton_pressed();

private:
    Ui::MainWindow *ui;
    Controller controller;
    void showlist();
};
#endif // MAINWINDOW_H
