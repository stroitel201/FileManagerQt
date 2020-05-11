#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLineEdit"
#include <QMessageBox>
#include <QHeaderView>
#include <QAbstractItemView>
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
    ui->filetableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    QStringList tableheader;
    ui->filetableWidget->setColumnCount(5);
    tableheader<<""<<"Name"<<"Expansion"<<"Size"<<"Last time write";
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

    QPixmap pixmap(":/icons/leftSmallArrowicon.png");
    QIcon ButtonIcon(pixmap);
    ui->lefttoolButton->setIcon(ButtonIcon);
    ui->lefttoolButton->setIconSize(QSize(pixmap.rect().size()));

    QPixmap pixmapR(":/icons/rightSmallArrowicon.png");
    QIcon ButtonIconR(pixmapR);
    ui->righttoolButton->setIcon(ButtonIconR);
    ui->righttoolButton->setIconSize(QSize(pixmapR.rect().size()));

    QMenu *menu = new QMenu(this);
    QAction* File = new QAction(tr("File"),this);
    File->setIcon(QIcon(":/icons/fileicon.png"));
    File->setIconVisibleInMenu(true);
    menu->addAction(File);
    QAction* Folder = new QAction(tr("Folder"),this);
    Folder->setIcon(QIcon(":/icons/foldericon.png"));
    Folder->setIconVisibleInMenu(true);
    menu->addAction(Folder);
    ui->createpushButton->setMenu(menu);

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
         controller.changeleftAdress();
        showlist();
    }
}

void MainWindow::on_leftGoToButton_clicked()
{
    ui->filetableWidget->clearSelection();
    if(ui->leftlineEdit->text()=="")return;
    QByteArray ba=ui->leftlineEdit->text().toLocal8Bit();
    int res = controller.LeftManager.CommandCD(ba.data());
    if (res==1) QMessageBox::critical(this,"Ошибка","Такой директории не существует");
    else
    {
         controller.changeleftAdress();
       showlist();
    }
}

void MainWindow::on_showHidcheckBox_stateChanged(int arg1)
{
    if(ui->showHidcheckBox->isChecked())
        controller.LeftManager.SetHidON();
    else controller.LeftManager.SetHidOFF();
    controller.LeftManager.GetFileFolders();

    showlist();
}

void MainWindow::on_openButton_clicked()
{
    if(controller.leftchosenfile.IsSubdir())
    {
        controller.LeftManager.setPath(controller.leftchosenfile.GetPath());
        controller.LeftManager.GetFileFolders();
        controller.changeleftAdress();
        showlist();

    }

    else controller.LeftManager.OpenFile(controller.leftchosenfile);
}


void MainWindow::showlist()
{
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();
    ui->filetableWidget->clearContents();
    auto it=controller.leftshowlist.begin();
    ui->filetableWidget->setRowCount(controller.leftshowlist.size());
    for (int i=0;it!=controller.leftshowlist.end();++it,++i)
    {
        QTableWidgetItem *icon_item = new QTableWidgetItem;
        icon_item->setTextAlignment(Qt::AlignCenter);
        icon_item->setFlags(Qt::NoItemFlags);
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
             folder->setFlags(Qt::NoItemFlags);
            ui->filetableWidget->setItem(i,2,folder);
            QTableWidgetItem* empty = new QTableWidgetItem("");
            empty->setFlags(Qt::NoItemFlags);
            ui->filetableWidget->setItem(i,3,empty);
            auto *timeinfo=it->GetTimeWrite();
            QString day; QString month; QString hour; QString min;
            if(timeinfo->tm_mday<10)
                day="0"+QString::number(timeinfo->tm_mday);
            else day=QString::number(timeinfo->tm_mday);
            if(timeinfo->tm_mon<10)
                month="0"+QString::number(timeinfo->tm_mon);
            else month=QString::number(timeinfo->tm_mon);
            if(timeinfo->tm_hour<10)
                hour="0"+QString::number(timeinfo->tm_hour);
            else hour=QString::number(timeinfo->tm_min);
            if(timeinfo->tm_min<10)
                min="0"+QString::number(timeinfo->tm_min);
            else min=QString::number(timeinfo->tm_min);
            QTableWidgetItem* time = new QTableWidgetItem(day+"."+
                                                          month+"."+
                                                          QString::number(timeinfo->tm_year+1900)+" "+
                                                          hour+":"+min);
            time->setFlags(Qt::NoItemFlags);
           // time->setTextAlignment(Qt::AlignLeft);
            ui->filetableWidget->setItem(i,4,time);
        }
        else
        {
            icon_item->setIcon(fileicon);
             ui->filetableWidget->setItem(i,0,icon_item);
             QTableWidgetItem* exp=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
             exp->setTextAlignment(Qt::AlignCenter);
             exp->setFlags(Qt::NoItemFlags);
            ui->filetableWidget->setItem(i,2,exp);
             QTableWidgetItem* size =new QTableWidgetItem(QString::number(it->GetSize())+" Bytes");
             size->setFlags(Qt::NoItemFlags);
            ui->filetableWidget->setItem(i,3,size);
            auto *timeinfo=it->GetTimeWrite();
            QString day; QString month; QString hour; QString min;
            if(timeinfo->tm_mday<10)
                day="0"+QString::number(timeinfo->tm_mday);
            else day=QString::number(timeinfo->tm_mday);
            if(timeinfo->tm_mon<10)
                month="0"+QString::number(timeinfo->tm_mon);
            else month=QString::number(timeinfo->tm_mon);
            if(timeinfo->tm_hour<10)
                hour="0"+QString::number(timeinfo->tm_hour);
            else hour=QString::number(timeinfo->tm_min);
            if(timeinfo->tm_min<10)
                min="0"+QString::number(timeinfo->tm_min);
            else min=QString::number(timeinfo->tm_min);
            QTableWidgetItem* time = new QTableWidgetItem(day+"."+
                                                          month+"."+
                                                          QString::number(timeinfo->tm_year+1900)+" "+
                                                          hour+":"+min);
            time->setFlags(Qt::NoItemFlags);
           // time->setTextAlignment(Qt::AlignLeft);
            ui->filetableWidget->setItem(i,4,time);
        }
    }
}



void MainWindow::on_lefttoolButton_pressed()
{
    if(controller.UndoAdress.size()==1)
        return;
    controller.leftUndo();
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();
    showlist();
}

void MainWindow::on_righttoolButton_pressed()
{
    if(controller.RedoAdress.size()==0)
        return;
    controller.leftRedo();
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();
    showlist();
}

void MainWindow::on_deletepushButton_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Удалить","Вы действительно хотите удалить файлы?",
                                                            QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::No)
        return;

    auto list=ui->filetableWidget->selectedItems();
    auto it=list.begin();
    for(;it!=list.end();++it)
    {
        QTableWidgetItem* item=*it;
         auto its=controller.leftshowlist.begin();
         for(;its!=controller.leftshowlist.end();++its)
         {
             string tmp=item->text().toStdString();
             if(tmp==its->GetName())
                 break;
         }
         controller.leftchosenfile=*its;
        int res=controller.LeftManager.CommandDEL(controller.leftchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
            return;
        }
    }
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();
    showlist();
}

void MainWindow::on_filetableWidget_clicked(const QModelIndex &index)
{
    auto list=ui->filetableWidget->selectedItems();
    if(list.size()==1)
    {
        on_filetableItem_Clicked(list.last());
        return;
    }
    ui->filetableWidget->clearSelection();
}
