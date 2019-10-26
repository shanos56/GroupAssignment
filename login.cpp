#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

    QString _username;
    QString _user = ui->lineEdit_username->text();

    if (_user.compare(_username) == 0) {
        if (ui->radioButton_online) {

        }
        this->close();
    } else {
        QMessageBox failureMessage (this);
        QMessageBox::warning(this,"Invalid Username","Username wasn't found in program.",QMessageBox::Ok);
    }


}

void Login::on_pushButton_Quit_clicked()
{
    QApplication::quit();

}
