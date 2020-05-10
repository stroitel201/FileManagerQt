#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLineEdit"
#include <QMessageBox>
#include <QHeaderView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller.leftdrives=controller.LeftManager.ShowDrive();
    for(auto it=controller.leftdrives.begin();it!=controller.leftdrives.end();++it)
        ui->drivelistWidget->addItem(QString::fromStdString(*it));
    connect(ui->drivelistWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(ondrivelistItemClicked(QListWidgetItem*)));
    connect(ui->filetableWidget,&QTableWidget::itemClicked,this,&MainWindow::on_filetableItem_Clicked);

    QStringList tableheader;
    ui->filetableWidget->setColumnCount(4);
    tableheader<<""<<"Name"<<"Expansion"<<"Size";
    ui->filetableWidget->setShowGrid(false);
    ui->filetableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->filetableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->filetableWidget->setHorizontalHeaderLabels(tableheader);
    ui->filetableWidget->setIconSize(QSize(25,25));
    ui->filetableWidget->setColumnWidth(0,10);
    ui->filetableWidget->setColumnWidth(1,200);
    if(QSysInfo::windowsVersion()==QSysInfo::WV_WINDOWS10){
        setStyleSheet(
            "QHeaderView::section{"
                "border-top:0px solid #D8D8D8;"
                "border-left:0px solid #D8D8D8;"
                "border-right:0px solid #D8D8D8;"
                "border-bottom: 0px solid #D8D8D8;"
                "background-color:white;"
                "padding:4px;"
            "}");}
    ui->filetableWidget->verticalHeader()->setVisible(false);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_filetableItem_Clicked(QTableWidgetItem* item)
{
   auto it=controller.leftshowlist.begin();
    for(;it!=controller.leftshowlist.end();++it)
    {
        string tmp=item->text().toStdString();
        if(tmp==it->GetName())
            break;
    }
    controller.leftchosenfile=*it;
}

void MainWindow::ondrivelistItemClicked(QListWidgetItem* item)
{
    int res = controller.LeftManager.CommandChangeDrive(item->text().toStdString());
    if(res==1) QMessageBox::critical(this,"Ошибка","Устройство не готово");
    else
    {
        controller.leftshowlist=controller.LeftManager.GetListOfFiles();
        ui->filetableWidget->clearContents();
        auto it=controller.leftshowlist.begin();
        ui->filetableWidget->setRowCount(controller.leftshowlist.size());

        for (int i=0;it!=controller.leftshowlist.end();++it,++i)
        {
            QTableWidgetItem *icon_item = new QTableWidgetItem;
            icon_item->setTextAlignment(Qt::AlignCenter);
            QPixmap p;
            if (!p.load(":/icons/foldericon.png") || p.isNull()) { cout << "Error!"; }
            QIcon foldericon = QIcon(p);
            if (!p.load(":/icons/fileicon.png") || p.isNull()) { cout << "Error!"; }
            QIcon fileicon = QIcon(p);
            ui->filetableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(it->GetName())));
            if(it->IsSubdir())
            {
                icon_item->setIcon(foldericon);
                 ui->filetableWidget->setItem(i,0,icon_item);
                 QTableWidgetItem* folder =new QTableWidgetItem("Folder");
                 folder->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,2,folder);
                ui->filetableWidget->setItem(i,3,new QTableWidgetItem(""));
            }
            else
            {
                icon_item->setIcon(fileicon);
                 ui->filetableWidget->setItem(i,0,icon_item);
                 QTableWidgetItem* exp=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
                 exp->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,2,exp);
                QTableWidgetItem* size=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
                exp->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,3,new QTableWidgetItem(QString::number(it->GetSize())+" Bytes"));
            }
        }
    }
}

void MainWindow::on_leftGoToButton_clicked()
{
    if(ui->leftlineEdit->text()=="")return;
    QByteArray ba=ui->leftlineEdit->text().toLocal8Bit();
    int res = controller.LeftManager.CommandCD(ba.data());
    if (res==1) QMessageBox::critical(this,"Ошибка","Такой директории не существует");
    else
    {
        controller.leftshowlist=controller.LeftManager.GetListOfFiles();
        ui->filetableWidget->clearContents();
        auto it=controller.leftshowlist.begin();
        ui->filetableWidget->setRowCount(controller.leftshowlist.size());

        for (int i=0;it!=controller.leftshowlist.end();++it,++i)
        {
            QTableWidgetItem *icon_item = new QTableWidgetItem;
            icon_item->setTextAlignment(Qt::AlignCenter);
            QPixmap p;
            if (!p.load(":/icons/foldericon.png") || p.isNull()) { cout << "Error!"; }
            QIcon foldericon = QIcon(p);
            if (!p.load(":/icons/fileicon.png") || p.isNull()) { cout << "Error!"; }
            QIcon fileicon = QIcon(p);
            ui->filetableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(it->GetName())));
            if(it->IsSubdir())
            {
                icon_item->setIcon(foldericon);
                 ui->filetableWidget->setItem(i,0,icon_item);
                 QTableWidgetItem* folder =new QTableWidgetItem("Folder");
                 folder->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,2,folder);
                ui->filetableWidget->setItem(i,3,new QTableWidgetItem(""));
            }
            else
            {
                icon_item->setIcon(fileicon);
                 ui->filetableWidget->setItem(i,0,icon_item);
                 QTableWidgetItem* exp=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
                 exp->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,2,exp);
                ui->filetableWidget->setItem(i,3,new QTableWidgetItem(QString::number(it->GetSize())+" Bytes"));
            }
        }
    }
}

void MainWindow::on_showHidcheckBox_stateChanged(int arg1)
{
    if(ui->showHidcheckBox->isChecked())
        controller.LeftManager.SetHidON();
    else controller.LeftManager.SetHidOFF();
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();
    ui->filetableWidget->clearContents();
    auto it=controller.leftshowlist.begin();
    ui->filetableWidget->setRowCount(controller.leftshowlist.size());

    for (int i=0;it!=controller.leftshowlist.end();++it,++i)
    {
        QTableWidgetItem *icon_item = new QTableWidgetItem;
        icon_item->setTextAlignment(Qt::AlignCenter);
        QPixmap p;
        if (!p.load(":/icons/foldericon.png") || p.isNull()) { cout << "Error!"; }
        QIcon foldericon = QIcon(p);
        if (!p.load(":/icons/fileicon.png") || p.isNull()) { cout << "Error!"; }
        QIcon fileicon = QIcon(p);
        ui->filetableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(it->GetName())));
        if(it->IsSubdir())
        {
            icon_item->setIcon(foldericon);
             ui->filetableWidget->setItem(i,0,icon_item);
             QTableWidgetItem* folder =new QTableWidgetItem("Folder");
             folder->setTextAlignment(Qt::AlignCenter);
            ui->filetableWidget->setItem(i,2,folder);
            ui->filetableWidget->setItem(i,3,new QTableWidgetItem(""));
        }
        else
        {
            icon_item->setIcon(fileicon);
             ui->filetableWidget->setItem(i,0,icon_item);
             QTableWidgetItem* exp=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
             exp->setTextAlignment(Qt::AlignCenter);
            ui->filetableWidget->setItem(i,2,exp);
            ui->filetableWidget->setItem(i,3,new QTableWidgetItem(QString::number(it->GetSize())+" Bytes"));
        }
    }
}

void MainWindow::on_openButton_clicked()
{
    if(controller.leftchosenfile.IsSubdir())
    {
        controller.LeftManager.setPath(controller.leftchosenfile.GetPath());
        controller.LeftManager.GetFileFolders();
        controller.leftshowlist=controller.LeftManager.GetListOfFiles();
        ui->filetableWidget->clearContents();
        auto it=controller.leftshowlist.begin();
        ui->filetableWidget->setRowCount(controller.leftshowlist.size());
        for (int i=0;it!=controller.leftshowlist.end();++it,++i)
        {
            QTableWidgetItem *icon_item = new QTableWidgetItem;
            icon_item->setTextAlignment(Qt::AlignCenter);
            QPixmap p;
            if (!p.load(":/icons/foldericon.png") || p.isNull()) { cout << "Error!"; }
            QIcon foldericon = QIcon(p);
            if (!p.load(":/icons/fileicon.png") || p.isNull()) { cout << "Error!"; }
            QIcon fileicon = QIcon(p);
            ui->filetableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(it->GetName())));
            if(it->IsSubdir())
            {
                icon_item->setIcon(foldericon);
                 ui->filetableWidget->setItem(i,0,icon_item);
                 QTableWidgetItem* folder =new QTableWidgetItem("Folder");
                 folder->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,2,folder);
                ui->filetableWidget->setItem(i,3,new QTableWidgetItem(""));
            }
            else
            {
                icon_item->setIcon(fileicon);
                 ui->filetableWidget->setItem(i,0,icon_item);
                 QTableWidgetItem* exp=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
                 exp->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,2,exp);
                QTableWidgetItem* size=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
                exp->setTextAlignment(Qt::AlignCenter);
                ui->filetableWidget->setItem(i,3,new QTableWidgetItem(QString::number(it->GetSize())+" Bytes"));
            }
        }
   }
    else controller.LeftManager.OpenFile(controller.leftchosenfile);
}
