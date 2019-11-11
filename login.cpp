#include "login.h"
#include "ui_login.h"
#include <QMessageBox>


Login::Login(std::shared_ptr<AbstractAssetRegister> reg, QWidget *parent) :
    QDialog(parent),
    _reg(reg),
    ui(new Ui::Login)

{
    ui->setupUi(this);
    this->setWindowTitle("Login");
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

    if (_user.compare("") == 0) {
            QMessageBox::warning(this,"Name Error","Please input a username.");
            return;
    }

    this->_reg.get()->setUsername(_user);


    if (ui->radioButton_online->isChecked()) {
         QMessageBox::warning(this,"Unimplemented","Loading from file hasn't been implemented. offline is the only option. \nNote: I worked alone in this assignment and didn't have time to implement everything.");
        /*emit loginSuccess(UI::FormStatus::LOADFILE);
        emit closeForm(UI::FormStatus::LOGIN);*/

    } else if (ui->radioButton_offline->isChecked()){
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
