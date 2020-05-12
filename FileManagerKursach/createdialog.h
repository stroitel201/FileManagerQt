#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class createDialog;
}

class createDialog : public QDialog
{
    Q_OBJECT


    signals:
    void createsig(const string &name, const bool& type);
public:
    explicit createDialog(QWidget *parent = nullptr);
    createDialog(bool type,bool side,QWidget *parent = nullptr);
    ~createDialog();

private slots:
    void on_buttonBox_rejected();

    void on_createDialog_accepted();

private:
     bool typec;
     bool side;
    Ui::createDialog *ui;
};

#endif // CREATEDIALOG_H
