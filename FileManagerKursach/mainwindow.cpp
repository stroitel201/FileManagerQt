#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "infodialog.h"
#include"createdialog.h"

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
    //connect(ui->filetableWidget,&QTableWidget::itemClicked,this,&MainWindow::on_filetableItem_Clicked);




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
    connect(File,SIGNAL(triggered()),this,SLOT(on_fileAction_clicked()));

    File->setIcon(QIcon(":/icons/fileicon.png"));
    File->setIconVisibleInMenu(true);
    menu->addAction(File);
    QAction* Folder = new QAction(tr("Folder"),this);
    connect(Folder,SIGNAL(triggered()),this,SLOT(on_folderAction_clicked()));
    Folder->setIcon(QIcon(":/icons/foldericon.png"));
    Folder->setIconVisibleInMenu(true);
    menu->addAction(Folder);
    ui->createpushButton->setMenu(menu);
/////////////////////////////////////////////////////////////////////////////////RIGHT/////////////////////
    controller.rightdrives=controller.RightManager.ShowDrive();
    for(auto it=controller.rightdrives.begin();it!=controller.rightdrives.end();++it)
        ui->drivelistWidgetR->addItem(QString::fromStdString(*it));
    connect(ui->drivelistWidgetR,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(ondrivelistItemClickedR(QListWidgetItem*)));
    //connect(ui->filetableWidget,&QTableWidget::itemClicked,this,&MainWindow::on_filetableItem_Clicked);




    ui->filetableWidgetR->setSelectionMode(QAbstractItemView::MultiSelection);

    QStringList tableheaderR;
    ui->filetableWidgetR->setColumnCount(5);
    tableheaderR<<""<<"Name"<<"Expansion"<<"Size"<<"Last time write";
    ui->filetableWidgetR->setShowGrid(false);
    ui->filetableWidgetR->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->filetableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->filetableWidgetR->setHorizontalHeaderLabels(tableheader);
    ui->filetableWidgetR->setIconSize(QSize(25,25));
    ui->filetableWidgetR->setColumnWidth(0,10);
    ui->filetableWidgetR->setColumnWidth(1,200);
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
    ui->filetableWidgetR->verticalHeader()->setVisible(false);

    QPixmap Rpixmap(":/icons/leftSmallArrowicon.png");
    QIcon RButtonIcon(Rpixmap);
    ui->lefttoolButtonR->setIcon(RButtonIcon);
    ui->lefttoolButtonR->setIconSize(QSize(Rpixmap.rect().size()));

    QPixmap RpixmapR(":/icons/rightSmallArrowicon.png");
    QIcon RButtonIconR(RpixmapR);
    ui->righttoolButtonR->setIcon(RButtonIconR);
    ui->righttoolButtonR->setIconSize(QSize(RpixmapR.rect().size()));

    QMenu *menuR = new QMenu(this);
    QAction* FileR = new QAction(tr("File"),this);
    connect(FileR,SIGNAL(triggered()),this,SLOT(on_fileAction_clickedR()));

    FileR->setIcon(QIcon(":/icons/fileicon.png"));
    FileR->setIconVisibleInMenu(true);
    menuR->addAction(FileR);
    QAction* FolderR = new QAction(tr("Folder"),this);
    connect(FolderR,SIGNAL(triggered()),this,SLOT(on_folderAction_clickedR()));
    FolderR->setIcon(QIcon(":/icons/foldericon.png"));
    FolderR->setIconVisibleInMenu(true);
    menuR->addAction(FolderR);
    ui->createpushButtonR->setMenu(menuR);

}

MainWindow::~MainWindow()
{
    delete ui;
}



/*void MainWindow::on_filetableItem_Clicked(QTableWidgetItem* item)
{
   auto it=controller.leftshowlist.begin();
    for(;it!=controller.leftshowlist.end();++it)
    {
        string tmp=item->text().toStdString();
        if(tmp==it->GetName())
            break;
    }
    controller.leftchosenfile=*it;
}*/

void MainWindow::ondrivelistItemClicked(QListWidgetItem* item)
{
    int res = controller.LeftManager.CommandChangeDrive(item->text().toStdString());
    if(res==1) QMessageBox::critical(this,"Ошибка","Устройство не готово");
    else
    {
        start=true;
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
    auto list=ui->filetableWidget->selectedItems();
    if(list.empty())return;
    QTableWidgetItem* item = list[0];
    auto its=controller.leftshowlist.begin();
    for(;its!=controller.leftshowlist.end();++its)
    {
        string tmp=item->text().toStdString();
        if(tmp==its->GetName())
            break;
    }
    controller.leftchosenfile=*its;
    if(controller.leftchosenfile.IsSubdir())
    {
        controller.LeftManager.setPath(controller.leftchosenfile.GetPath());
        controller.LeftManager.GetFileFolders();
        controller.changeleftAdress();
        showlist();
        ui->filetableWidget->clearSelection();
    }

    else
    {
        controller.LeftManager.OpenFile(controller.leftchosenfile);
        ui->filetableWidget->clearSelection();
    }
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
        ui->leftlineEdit->setText(QString::fromUtf8(controller.LeftManager.getPath()));
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
    auto list=ui->filetableWidget->selectedItems();
    if(list.empty())return;
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Удалить","Вы действительно хотите удалить файлы?",
                                                            QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::No)
        return;


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
         if(controller.leftchosenfile.IsRdonly())
         {
             QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
             return;
         }
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

     ui->filetableWidget->clearSelection();
}

void MainWindow::on_filetableWidget_clicked(const QModelIndex &index)
{
    auto list=ui->filetableWidget->selectedItems();
    if(list.size()==1)
    {
        //on_filetableItem_Clicked(list.last());
        return;
    }
    else if(list.size()==2)
    {
        QTableWidgetItem* temp=list.last();
        ui->filetableWidget->clearSelection();
        ui->filetableWidget->setItemSelected(temp,true);
        return;
    }
    ui->filetableWidget->clearSelection();
}

void MainWindow::on_infopushButton_clicked()
{
    auto list=ui->filetableWidget->selectedItems();
    if(list.empty())return;
    QTableWidgetItem* item = list[0];
    auto its=controller.leftshowlist.begin();
    for(;its!=controller.leftshowlist.end();++its)
    {
        string tmp=item->text().toStdString();
        if(tmp==its->GetName())
            break;
    }
    controller.leftchosenfile=*its;
    File* tmp=&controller.leftchosenfile;
    ui->filetableWidget->clearSelection();
    infoDialog info(tmp,true,this);
    //connect(&info, SIGNAL(renamesig(string name)), SLOT(on_rename_clicked(string name)));
    info.setModal(true);
    info.exec();

}

void MainWindow::on_rename_recieve(const string &name)
{

   int result = controller.LeftManager.CommandRENAME(controller.leftchosenfile,name.c_str());
   if(result==1)
   {
       QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
       return;
   }
   controller.LeftManager.GetFileFolders();
   controller.leftshowlist=controller.LeftManager.GetListOfFiles();
   showlist();

    return;
}

void MainWindow::on_filetableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    auto its=controller.leftshowlist.begin();
    for(;its!=controller.leftshowlist.end();++its)
    {
        string tmp=item->text().toStdString();
        if(tmp==its->GetName())
            break;
    }
    controller.leftchosenfile=*its;
    if(controller.leftchosenfile.IsSubdir())
    {
        controller.LeftManager.setPath(controller.leftchosenfile.GetPath());
        controller.LeftManager.GetFileFolders();
        controller.changeleftAdress();
        showlist();
        ui->filetableWidget->clearSelection();
    }

    else
    {
        controller.LeftManager.OpenFile(controller.leftchosenfile);
        ui->filetableWidget->clearSelection();
    }
}

void MainWindow::on_checkbox_recieve(const bool& flagattr, const bool& flagtumb)
{
    if(flagattr==true&&flagtumb==true)
    {
        int res=controller.LeftManager.CommandChangeRdoAttr(controller.leftchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }

    }
    if(flagattr==true&&flagtumb==false)
    {
        int res=controller.LeftManager.CommandResetRdoAttr(controller.leftchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
    }
    if(flagattr==false&&flagtumb==true)
    {
        int res=controller.LeftManager.CommandChangeHidAttr(controller.leftchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
    }
    if(flagattr==false&&flagtumb==false)
    {
        int res=controller.LeftManager.CommandResetHidAttr(controller.leftchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
    }

}

void MainWindow::close_recieve()
{
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();
    showlist();
}
void MainWindow::on_fileAction_clicked()
{
    if(start==false)
        return;
    createDialog info(false,true,this);

    info.setModal(true);
    info.exec();
}
void MainWindow::on_folderAction_clicked()
{
    if(start==false)
        return;
    createDialog info(true,true,this);

    info.setModal(true);
    info.exec();
}
void MainWindow::on_create_recieve(const string& name,bool type)
{
    if(type)
    {
        int res=controller.LeftManager.CommandMKDIR(name.c_str());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
        controller.LeftManager.GetFileFolders();
        controller.leftshowlist=controller.LeftManager.GetListOfFiles();
        showlist();
    }
    else
    {
        int res=controller.LeftManager.CommandFILE(name.c_str());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
        controller.LeftManager.GetFileFolders();
        controller.leftshowlist=controller.LeftManager.GetListOfFiles();
        showlist();
    }

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void MainWindow::ondrivelistItemClickedR(QListWidgetItem* item)
{
    int res = controller.RightManager.CommandChangeDrive(item->text().toStdString());
    if(res==1) QMessageBox::critical(this,"Ошибка","Устройство не готово");
    else
    {
        start=true;
         controller.changerightAdress();
        showlistR();
    }

}

void MainWindow::on_leftGoToButtonR_clicked()
{
    ui->filetableWidgetR->clearSelection();
    if(ui->leftlineEditR->text()=="")return;
    QByteArray ba=ui->leftlineEditR->text().toLocal8Bit();
    int res = controller.RightManager.CommandCD(ba.data());
    if (res==1) QMessageBox::critical(this,"Ошибка","Такой директории не существует");
    else
    {
         controller.changerightAdress();
       showlistR();
    }
}

void MainWindow::on_showHidcheckBoxR_stateChanged(int arg1)
{
    if(ui->showHidcheckBoxR->isChecked())
        controller.RightManager.SetHidON();
    else controller.RightManager.SetHidOFF();
    controller.RightManager.GetFileFolders();

    showlistR();
}

void MainWindow::on_openButtonR_clicked()
{
    auto list=ui->filetableWidgetR->selectedItems();
    if(list.empty())return;
    QTableWidgetItem* item = list[0];
    auto its=controller.rightshowlist.begin();
    for(;its!=controller.rightshowlist.end();++its)
    {
        string tmp=item->text().toStdString();
        if(tmp==its->GetName())
            break;
    }
    controller.rightchosenfile=*its;
    if(controller.rightchosenfile.IsSubdir())
    {
        controller.RightManager.setPath(controller.rightchosenfile.GetPath());
        controller.RightManager.GetFileFolders();
        controller.changerightAdress();
        showlistR();
        ui->filetableWidgetR->clearSelection();
    }

    else
    {
        controller.RightManager.OpenFile(controller.rightchosenfile);
        ui->filetableWidgetR->clearSelection();
    }
}


void MainWindow::showlistR()
{
    controller.rightshowlist=controller.RightManager.GetListOfFiles();
    ui->filetableWidgetR->clearContents();
    auto it=controller.rightshowlist.begin();
    ui->filetableWidgetR->setRowCount(controller.rightshowlist.size());
    for (int i=0;it!=controller.rightshowlist.end();++it,++i)
    {
        QTableWidgetItem *icon_item = new QTableWidgetItem;
        icon_item->setTextAlignment(Qt::AlignCenter);
        icon_item->setFlags(Qt::NoItemFlags);
        QPixmap p;
        if (!p.load(":/icons/foldericon.png") || p.isNull()) { cout << "Error!"; }
        QIcon foldericon = QIcon(p);
        if (!p.load(":/icons/fileicon.png") || p.isNull()) { cout << "Error!"; }
        QIcon fileicon = QIcon(p);
        ui->filetableWidgetR->setItem(i,1,new QTableWidgetItem(QString::fromStdString(it->GetName())));
        if(it->IsSubdir())
        {
            icon_item->setIcon(foldericon);
             ui->filetableWidgetR->setItem(i,0,icon_item);
             QTableWidgetItem* folder =new QTableWidgetItem("Folder");
             folder->setTextAlignment(Qt::AlignCenter);
             folder->setFlags(Qt::NoItemFlags);
            ui->filetableWidgetR->setItem(i,2,folder);
            QTableWidgetItem* empty = new QTableWidgetItem("");
            empty->setFlags(Qt::NoItemFlags);
            ui->filetableWidgetR->setItem(i,3,empty);
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
            ui->filetableWidgetR->setItem(i,4,time);
        }
        else
        {
            icon_item->setIcon(fileicon);
             ui->filetableWidgetR->setItem(i,0,icon_item);
             QTableWidgetItem* exp=new QTableWidgetItem(QString::fromStdString(it->GetExp()));
             exp->setTextAlignment(Qt::AlignCenter);
             exp->setFlags(Qt::NoItemFlags);
            ui->filetableWidgetR->setItem(i,2,exp);
             QTableWidgetItem* size =new QTableWidgetItem(QString::number(it->GetSize())+" Bytes");
             size->setFlags(Qt::NoItemFlags);
            ui->filetableWidgetR->setItem(i,3,size);
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
            ui->filetableWidgetR->setItem(i,4,time);
        }
        ui->leftlineEditR->setText(QString::fromUtf8(controller.RightManager.getPath()));
    }
}



void MainWindow::on_lefttoolButtonR_pressed()
{
    if(controller.rightUndoAdress.size()==1)
        return;
    controller.rightUndo();
    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();
    showlistR();
}

void MainWindow::on_righttoolButtonR_pressed()
{
    if(controller.rightRedoAdress.size()==0)
        return;
    controller.rightRedo();
    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();
    showlistR();
}

void MainWindow::on_deletepushButtonR_clicked()
{
    auto list=ui->filetableWidgetR->selectedItems();
    if(list.empty())return;
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Удалить","Вы действительно хотите удалить файлы?",
                                                            QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::No)
        return;


    auto it=list.begin();
    for(;it!=list.end();++it)
    {
        QTableWidgetItem* item=*it;
         auto its=controller.rightshowlist.begin();
         for(;its!=controller.rightshowlist.end();++its)
         {
             string tmp=item->text().toStdString();
             if(tmp==its->GetName())
                 break;
         }
         controller.rightchosenfile=*its;
         if(controller.rightchosenfile.IsRdonly())
         {
             QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
             return;
         }
        int res=controller.RightManager.CommandDEL(controller.rightchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
            return;
        }
    }
    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();

    showlistR();

     ui->filetableWidgetR->clearSelection();
}

void MainWindow::on_filetableWidgetR_clicked(const QModelIndex &index)
{
    auto list=ui->filetableWidgetR->selectedItems();
    if(list.size()==1)
    {
        //on_filetableItem_Clicked(list.last());
        return;
    }
    else if(list.size()==2)
    {
        QTableWidgetItem* temp=list.last();
        ui->filetableWidgetR->clearSelection();
        ui->filetableWidgetR->setItemSelected(temp,true);
        return;
    }
    ui->filetableWidgetR->clearSelection();
}

void MainWindow::on_infopushButtonR_clicked()
{
    auto list=ui->filetableWidgetR->selectedItems();
    if(list.empty())return;
    QTableWidgetItem* item = list[0];
    auto its=controller.rightshowlist.begin();
    for(;its!=controller.rightshowlist.end();++its)
    {
        string tmp=item->text().toStdString();
        if(tmp==its->GetName())
            break;
    }
    controller.rightchosenfile=*its;
    File* tmp=&controller.rightchosenfile;
    ui->filetableWidgetR->clearSelection();
    infoDialog info(tmp,false,this);
    //connect(&info, SIGNAL(renamesig(string name)), SLOT(on_rename_clicked(string name)));
    info.setModal(true);
    info.exec();

}

void MainWindow::on_rename_recieveR(const string &name)
{

   int result = controller.RightManager.CommandRENAME(controller.rightchosenfile,name.c_str());
   if(result==1)
   {
       QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
       return;
   }
   controller.RightManager.GetFileFolders();
   controller.rightshowlist=controller.RightManager.GetListOfFiles();
   showlistR();

    return;
}

void MainWindow::on_filetableWidgetR_itemDoubleClicked(QTableWidgetItem *item)
{
    auto its=controller.rightshowlist.begin();
    for(;its!=controller.rightshowlist.end();++its)
    {
        string tmp=item->text().toStdString();
        if(tmp==its->GetName())
            break;
    }
    controller.rightchosenfile=*its;
    if(controller.rightchosenfile.IsSubdir())
    {
        controller.RightManager.setPath(controller.rightchosenfile.GetPath());
        controller.RightManager.GetFileFolders();
        controller.changerightAdress();
        showlistR();
        ui->filetableWidgetR->clearSelection();
    }

    else
    {
        controller.RightManager.OpenFile(controller.rightchosenfile);
        ui->filetableWidgetR->clearSelection();
    }
}

void MainWindow::on_checkbox_recieveR(const bool& flagattr, const bool& flagtumb)
{
    if(flagattr==true&&flagtumb==true)
    {
        int res=controller.RightManager.CommandChangeRdoAttr(controller.rightchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }

    }
    if(flagattr==true&&flagtumb==false)
    {
        int res=controller.RightManager.CommandResetRdoAttr(controller.rightchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
    }
    if(flagattr==false&&flagtumb==true)
    {
        int res=controller.RightManager.CommandChangeHidAttr(controller.rightchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
    }
    if(flagattr==false&&flagtumb==false)
    {
        int res=controller.RightManager.CommandResetHidAttr(controller.rightchosenfile);
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
    }

}

void MainWindow::close_recieveR()
{
    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();
    showlistR();
}
void MainWindow::on_fileAction_clickedR()
{
    if(start==false)
        return;
    createDialog info(false,false,this);

    info.setModal(true);
    info.exec();
}
void MainWindow::on_folderAction_clickedR()
{
    if(start==false)
        return;
    createDialog info(true,false,this);

    info.setModal(true);
    info.exec();
}
void MainWindow::on_create_recieveR(const string& name,bool type)
{
    if(type)
    {
        int res=controller.RightManager.CommandMKDIR(name.c_str());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
        controller.RightManager.GetFileFolders();
        controller.rightshowlist=controller.RightManager.GetListOfFiles();
        showlistR();
    }
    else
    {
        int res=controller.RightManager.CommandFILE(name.c_str());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Не удалось");
            return;
        }
        controller.RightManager.GetFileFolders();
        controller.rightshowlist=controller.RightManager.GetListOfFiles();
        showlistR();
    }

}

void MainWindow::on_copypushButton_clicked()
{
    auto list=ui->filetableWidget->selectedItems();
    if(list.empty())return;


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

        int res=controller.LeftManager.CommandCOPY(controller.leftchosenfile,controller.RightManager.getPath());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа");
            return;
        }
    }
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();

    showlist();

    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();

    showlistR();
     ui->filetableWidget->clearSelection();
}

void MainWindow::on_copypushButtonR_clicked()
{
    auto list=ui->filetableWidgetR->selectedItems();
    if(list.empty())return;


    auto it=list.begin();
    for(;it!=list.end();++it)
    {
        QTableWidgetItem* item=*it;
         auto its=controller.rightshowlist.begin();
         for(;its!=controller.rightshowlist.end();++its)
         {
             string tmp=item->text().toStdString();
             if(tmp==its->GetName())
                 break;
         }
         controller.rightchosenfile=*its;

        int res=controller.RightManager.CommandCOPY(controller.rightchosenfile,controller.LeftManager.getPath());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа");
            return;
        }
    }
    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();

    showlistR();

    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();

    showlist();
     ui->filetableWidgetR->clearSelection();
}

void MainWindow::on_movepushButton_clicked()
{
    auto list=ui->filetableWidget->selectedItems();
    if(list.empty())return;


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
         if(controller.leftchosenfile.IsRdonly())
         {
             QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
             return;
         }
        int res=controller.LeftManager.CommandMOVE(controller.leftchosenfile,controller.RightManager.getPath());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа");
            return;
        }
    }
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();

    showlist();

    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();

    showlistR();
     ui->filetableWidget->clearSelection();
}

void MainWindow::on_movepushButtonR_clicked()
{
    auto list=ui->filetableWidgetR->selectedItems();
    if(list.empty())return;


    auto it=list.begin();
    for(;it!=list.end();++it)
    {
        QTableWidgetItem* item=*it;
         auto its=controller.rightshowlist.begin();
         for(;its!=controller.rightshowlist.end();++its)
         {
             string tmp=item->text().toStdString();
             if(tmp==its->GetName())
                 break;
         }
         controller.rightchosenfile=*its;
         if(controller.rightchosenfile.IsRdonly())
         {
             QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа или файл занят другим процессом");
             return;
         }
        int res=controller.RightManager.CommandMOVE(controller.rightchosenfile,controller.LeftManager.getPath());
        if(res==1)
        {
            QMessageBox::critical(this,"Ошибка","Возможно у вас нет доступа");
            return;
        }
    }
    controller.LeftManager.GetFileFolders();
    controller.leftshowlist=controller.LeftManager.GetListOfFiles();

    showlist();

    controller.RightManager.GetFileFolders();
    controller.rightshowlist=controller.RightManager.GetListOfFiles();

    showlistR();
     ui->filetableWidget->clearSelection();
}
