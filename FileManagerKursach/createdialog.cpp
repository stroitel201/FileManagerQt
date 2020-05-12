#include "createdialog.h"
#include "ui_createdialog.h"

createDialog::createDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createDialog)
{
    ui->setupUi(this);
}

createDialog::createDialog(bool type,bool side,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createDialog)
{
    ui->setupUi(this);
    this->side=side;
    this->typec=type;
    if (side)
        connect(this,SIGNAL(createsig(string,bool)),parent,SLOT(on_create_recieve(string,bool)));
    else connect(this,SIGNAL(createsig(string,bool)),parent,SLOT(on_create_recieveR(string,bool)));
    if(type)
    {
        QPixmap pix("C:/Users/olegv/source/repos/FileManagerKursach/foldericon.png");
        ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
    }
    else
    {
        QPixmap pix("C:/Users/olegv/source/repos/FileManagerKursach/fileicon.png");
         ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
    }

}

createDialog::~createDialog()
{
    delete ui;
}

void createDialog::on_buttonBox_rejected()
{
    close();
}

void createDialog::on_createDialog_accepted()
{
    if(typec) emit createsig(ui->createlineEdit->text().toStdString(),true);
    else emit createsig(ui->createlineEdit->text().toStdString(),false);
}
