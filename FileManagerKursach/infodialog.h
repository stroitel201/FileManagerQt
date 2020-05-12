#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class infoDialog;
}

class infoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit infoDialog(QWidget *parent = nullptr);
    infoDialog(File* file,bool side,QWidget *parent = nullptr);
    ~infoDialog();

signals:
    void checkboxsig(const bool& flagattr, const bool& flagtumb);
    void renamesig(const string &name);
    void closesig();
private slots:
    void on_okpushButton_clicked();
    void on_renamepushButton_clicked();


    void on_rdocheckBox_stateChanged(int arg1);

    void on_hidcheckBox_stateChanged(int arg1);

private:
    int checkboxflag=1;
    bool side;
    File filec;
    Ui::infoDialog *ui;
};

#endif // INFODIALOG_H
