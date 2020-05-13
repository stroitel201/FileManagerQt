#include "createdialog.h"
#include "ui_createdialog.h"
#include <QTextCodec>
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
    QPixmap pixmapM(":/icons/main.png");
    QIcon ButtonIconM(pixmapM);
    setWindowIcon(ButtonIconM);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    this->side=side;
    this->typec=type;
    if (side)
        connect(this,SIGNAL(createsig(string,bool)),parent,SLOT(on_create_recieve(string,bool)));
    else connect(this,SIGNAL(createsig(string,bool)),parent,SLOT(on_create_recieveR(string,bool)));
    if(type)
    {
        QPixmap pix(":/icons/foldericon.png");
        ui->piclabel->setScaledContents(true);
        ui->piclabel->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/icons/fileicon.png");
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
    if(ui->createlineEdit->text()=="")
        return;
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
      QByteArray tmp = codec->fromUnicode(ui->createlineEdit->text());


    if(typec) emit createsig(string(tmp),true);
    else emit createsig(string(tmp),false);
}
