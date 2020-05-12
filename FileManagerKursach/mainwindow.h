#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include "infodialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void on_checkbox_recieve(const bool& flagattr, const bool& flagtumb);
     void on_rename_recieve(const string &name);
     void close_recieve();
     void on_create_recieve(const string &name,bool type);
private slots:
    void on_leftGoToButton_clicked();
    void ondrivelistItemClicked(QListWidgetItem* item);
    void on_showHidcheckBox_stateChanged(int arg1);
    //void on_filetableItem_Clicked(QTableWidgetItem* item);
     void on_openButton_clicked();

    void on_fileAction_clicked();
     void on_folderAction_clicked();
     void on_lefttoolButton_pressed();

     void on_righttoolButton_pressed();

     void on_deletepushButton_clicked();

     void on_filetableWidget_clicked(const QModelIndex &index);

     void on_infopushButton_clicked();

     void on_filetableWidget_itemDoubleClicked(QTableWidgetItem *item);

     void on_actionExit_triggered();

private:
    bool start=false;
    Ui::MainWindow *ui;
    Controller controller;
    void showlist();
};
#endif // MAINWINDOW_H
