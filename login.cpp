#include "login.h"
#include "ui_login.h"
#include <QMessageBox>


Login::Login(std::shared_ptr<AbstractAssetRegister> reg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),
    _reg(reg)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_Quit_clicked()
{
   emit this->closeForm(UI::FormStatus::LOGIN);

}


void Login::on_pushButton_login_clicked()
{
    QString _user = ui->lineEdit_username->text();
    qDebug() << "Login button Working";
    this->_reg.get()->setUsername(_user);


    qDebug() << "Login button Working";

    if (ui->radioButton_online->isChecked()) {
         qDebug() << "online button checked";
        emit loginSuccess(UI::FormStatus::LOADFILE);
        emit closeForm(UI::FormStatus::LOGIN);

    } else if (ui->radioButton_offline->isChecked()){
        qDebug() << "offline button checked";
       emit loginSuccess(UI::FormStatus::MAIN);
       emit closeForm(UI::FormStatus::LOGIN);
    }else {
        QMessageBox failureMessage (this);
        QMessageBox::warning(this,"Invalid Username","Invalid Username.",QMessageBox::Ok);
    }
}

void Login::on_Login_destroyed()
{





}
