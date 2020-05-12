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

     //////////////////////////////////////////////

     void on_checkbox_recieveR(const bool& flagattr, const bool& flagtumb);
      void on_rename_recieveR(const string &name);
      void close_recieveR();
      void on_create_recieveR(const string &name,bool type);
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

     //////////////////////////////////////////////

     void on_leftGoToButtonR_clicked();
     void ondrivelistItemClickedR(QListWidgetItem* item);
     void on_showHidcheckBoxR_stateChanged(int arg1);
     //void on_filetableItem_Clicked(QTableWidgetItem* item);
      void on_openButtonR_clicked();

     void on_fileAction_clickedR();
      void on_folderAction_clickedR();
      void on_lefttoolButtonR_pressed();

      void on_righttoolButtonR_pressed();

      void on_deletepushButtonR_clicked();

      void on_filetableWidgetR_clicked(const QModelIndex &index);

      void on_infopushButtonR_clicked();

      void on_filetableWidgetR_itemDoubleClicked(QTableWidgetItem *item);



      void on_copypushButton_clicked();

      void on_copypushButtonR_clicked();

private:
    bool start=false;
    bool startR=false;
    Ui::MainWindow *ui;
    Controller controller;
    void showlist();
    void showlistR();
};
#endif // MAINWINDOW_H
