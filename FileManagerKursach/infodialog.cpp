#include "infodialog.h"
#include "ui_infodialog.h"
#include <QTextCodec>
#include<QFlag>
infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoDialog)
{

 ui->setupUi(this);
}

infoDialog::infoDialog(File* file,bool side,QWidget *parent):
    QDialog(parent),
    ui(new Ui::infoDialog)
{

    ui->setupUi(this);
    QPixmap pixmapM(":/icons/main.png");
    QIcon ButtonIconM(pixmapM);
    setWindowIcon(ButtonIconM);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    this->side=side;
    //connect(ui->renamepushButton,SIGNAL(clicked()),this,SLOT(on_okpushButton_clicked()));
    if(side)
    {
        connect(this,SIGNAL(renamesig(string)),parent,SLOT(on_rename_recieve(string)));
        connect(this,SIGNAL(checkboxsig(bool,bool)),parent,SLOT(on_checkbox_recieve(bool,bool)));
        connect(this,SIGNAL(closesig()),parent,SLOT(close_recieve()));
    }
    else
    {
        connect(this,SIGNAL(renamesig(string)),parent,SLOT(on_rename_recieveR(string)));
        connect(this,SIGNAL(checkboxsig(bool,bool)),parent,SLOT(on_checkbox_recieveR(bool,bool)));
        connect(this,SIGNAL(closesig()),parent,SLOT(close_recieveR()));
    }
    this->filec=*file;
    if (file->IsSubdir())
    {
        QPixmap pix(":/icons/foldericon.png");
        ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
         ui->sizelabel->setText("");
    }
    else
    {
        QPixmap pix(":/icons/fileicon.png");
         ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
         ui->sizelabel->setText("Size: "+QString::number((unsigned long long)file->GetSize())+" Bytes");
    }
    if(file->IsHidden())
        ui->hidcheckBox->setCheckState(Qt::Checked);
    if(file->IsRdonly())
        ui->rdocheckBox->setCheckState(Qt::Checked);
    checkboxflag=0;
    char path[MAX_PATH];
    strcpy(path,file->GetPath());
    *(strrchr(path,'\\')+1)='\0';
    ui->pathlabel->setText("Path: "+ QString::fromLocal8Bit(path));
    ui->namelineEdit->setText(QString::fromLocal8Bit(file->GetName().c_str()));
    auto *timeinfo=file->GetTimeWrite();
    QString day; QString month; QString hour; QString min;
    if(timeinfo->tm_mday<10)
        day="0"+QString::number(timeinfo->tm_mday);
    else day=QString::number(timeinfo->tm_mday);
    if(timeinfo->tm_mon<10)
        month="0"+QString::number(timeinfo->tm_mon);
    else month=QString::number(timeinfo->tm_mon);
    if(timeinfo->tm_hour<10)
        hour="0"+QString::number(timeinfo->tm_hour);
    else hour=QString::number(timeinfo->tm_hour);
    if(timeinfo->tm_min<10)
        min="0"+QString::number(timeinfo->tm_min);
    else min=QString::number(timeinfo->tm_min);
    ui->timewritelabel->setText("Last time write: "+day+"."+month+"."+QString::number(timeinfo->tm_year+1900)+" "+hour+":"+min);

    timeinfo=file->GetTimeCreate();
    if(timeinfo->tm_mday<10)
        day="0"+QString::number(timeinfo->tm_mday);
    else day=QString::number(timeinfo->tm_mday);
    if(timeinfo->tm_mon<10)
        month="0"+QString::number(timeinfo->tm_mon);
    else month=QString::number(timeinfo->tm_mon);
    if(timeinfo->tm_hour<10)
        hour="0"+QString::number(timeinfo->tm_hour);
    else hour=QString::number(timeinfo->tm_hour);
    if(timeinfo->tm_min<10)
        min="0"+QString::number(timeinfo->tm_min);
    else min=QString::number(timeinfo->tm_min);
     ui->timecreatelabel->setText("Time create: "+day+"."+month+"."+QString::number(timeinfo->tm_year+1900)+" "+hour+":"+min);

     ui->pathlabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

infoDialog::~infoDialog()
{
    delete ui;
}

void infoDialog::on_okpushButton_clicked()
{
    emit closesig();
    close();
}

void infoDialog::on_renamepushButton_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
      QByteArray tmp = codec->fromUnicode(ui->namelineEdit->text());

    if(tmp==filec.GetName().c_str())
        return;
    else emit renamesig(string(tmp));

    close();
}


void infoDialog::on_rdocheckBox_stateChanged(int arg1)
{
    if(checkboxflag)
        return;
    if(ui->rdocheckBox->isChecked()&&arg1==Qt::CheckState::Checked)
        emit checkboxsig(true,true);
    if(ui->rdocheckBox->checkState()==Qt::CheckState::Unchecked && arg1==Qt::CheckState::Unchecked)
        emit checkboxsig(true,false);
}

void infoDialog::on_hidcheckBox_stateChanged(int arg1)
{
    if(checkboxflag)
        return;
    if(ui->hidcheckBox->isChecked()&&arg1==Qt::CheckState::Checked)
        emit checkboxsig(false,true);
    if(ui->hidcheckBox->checkState()==Qt::CheckState::Unchecked && arg1==Qt::CheckState::Unchecked)
        emit checkboxsig(false,false);
}
