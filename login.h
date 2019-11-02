#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "assetregister.h"
#include "formstatus.h"


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

    std::shared_ptr<AbstractAssetRegister> _reg;

public:
    explicit Login(std::shared_ptr<AbstractAssetRegister> reg, QWidget *parent = nullptr);
    ~Login();



signals:
    void loginSuccess(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void closeForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);

private slots:

    void on_pushButton_Quit_clicked();

    void on_pushButton_login_clicked();

    void on_Login_destroyed();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
