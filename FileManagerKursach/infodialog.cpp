#include "infodialog.h"
#include "ui_infodialog.h"

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
        QPixmap pix("C:/Users/olegv/source/repos/FileManagerKursach/foldericon.png");
        ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
         ui->sizelabel->setText("");
    }
    else
    {
        QPixmap pix("C:/Users/olegv/source/repos/FileManagerKursach/fileicon.png");
         ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
         ui->sizelabel->setText("Size: "+QString::number(file->GetSize())+" Bytes");
    }
    if(file->IsHidden())
        ui->hidcheckBox->setCheckState(Qt::Checked);
    if(file->IsRdonly())
        ui->rdocheckBox->setCheckState(Qt::Checked);
    checkboxflag=0;
    char path[MAX_PATH];
    strcpy(path,file->GetPath());
    *(strrchr(path,'\\')+1)='\0';
    ui->pathlabel->setText("Path: "+ QString::fromUtf8(path));
    ui->namelineEdit->setText(QString::fromStdString(file->GetName()));
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

    if(ui->namelineEdit->text().toStdString()==filec.GetName())
        return;
    else emit renamesig(ui->namelineEdit->text().toStdString());
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
