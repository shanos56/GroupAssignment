#ifndef FORMSTATUSHANDLER_H
#define FORMSTATUSHANDLER_H

#include <QObject>
#include <QStack>
#include <QDialog>
#include <QDebug>
#include <QApplication>
#include "login.h"
#include "mainwindow.h"
#include "assetregister.h"
#include "assettypeform.h"
#include "custodianform.h"
#include "assetform.h"
#include "userpropertyform.h"
namespace UI {
class FormStatusHandler: public QObject
{

    Q_OBJECT


    QStack<FormStatus> status;
    QStack<std::shared_ptr<QDialog>> dialogs;
    QApplication &_app;

    std::shared_ptr<AbstractAssetRegister> _reg;

    std::shared_ptr<QMainWindow> _window;

    bool mainWindowOpen = false;


    void addDialog (FormStatus stat, QString id = "") {

        switch (stat) {

            case LOGIN: {
                std::shared_ptr<QDialog>form {new Login(_reg,_window.get())};
                this->dialogs.append(form);
                QObject::connect(form.get(),SIGNAL(loginSuccess(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
                QObject::connect(form.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
                showWindow();
                break;
            }

            case MAIN: {
                this->_window = std::shared_ptr<QMainWindow>(new MainWindow(this->_reg));
                this->dialogs.append(nullptr);
                QObject::connect(this->_window.get(),SIGNAL(openForm(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
                QObject::connect(this->_window.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
                QObject::connect(this->_window.get(),SIGNAL(openForm(UI::FormStatus,QString)),this,SLOT(setStatus(UI::FormStatus, QString)));
                mainWindowOpen = true;
                showWindow();
                break;
            }

            case FormStatus::EDITASSETTYPE: {
                std::shared_ptr<QDialog>form {new AssetTypeForm(_reg,id,_window.get())};
                this->dialogs.append(form);
                this->setSignals(form);
                showWindow();
                break;
            }
            
        case FormStatus::EDITCUSTODIAN: {
            std::shared_ptr<QDialog>form {new CustodianForm(_reg,id,_window.get())};
            this->dialogs.append(form);
             this->setSignals(form);
            showWindow();
            break;
        }

        case FormStatus::EDITASSET: {
            std::shared_ptr<QDialog>form {new AssetForm(_reg,id,_window.get())};
            this->dialogs.append(form);
            QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
            QObject::connect(form.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
            QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus,QString)),this,SLOT(setStatus(UI::FormStatus, QString)));
            showWindow();
            break;
        }

        case FormStatus::USERPROPERTY: {
            std::shared_ptr<QDialog>form {new UserPropertyForm(_reg,id,_window.get())};
            this->dialogs.append(form);
            QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
            QObject::connect(form.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
            QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus,QString)),this,SLOT(setStatus(UI::FormStatus, QString)));
            showWindow();
            break;
        }
        default:
            break;

        }
    }

    void closeDialog(FormStatus stat) {
        this->closeDialog(this->status.indexOf(stat));

    }

    void showWindow() {
        if (this->getStatus() == MAIN) {
            if (this->status.size() > 1) {
                auto dia = this->dialogs.at(this->dialogs.size()-2).get();
                if (!dia->isHidden())
                    dia->hide();
            }
            _window->show();
        } else {
            if (this->status.size() > 1) {
                qDebug()<<"show window";

                hideWindow(this->dialogs.size()-2);
            }
            this->dialogs.last()->show();
        }

    }

    void hideWindow(int at) {
        auto dia = this->dialogs.at(at).get();
        if (dia == nullptr) {
            qDebug() << "main window hidden";
            this->_window->hide();
        } else if (!dia->isHidden()) {
            dia->hide();
        }

    }

    bool closeDialog(int index) {

       if (index != -1 && index <= dialogs.size()) {
            auto form = this->dialogs.at(index).get();
            if (form == nullptr) {
                this->_window->disconnect();
                this->_window->close();
            }else {
                form->disconnect();
                form->close();
            }
            return true;
        } else {
            return false;
        }
    }

    void closeApplication () {
        QApplication::exit();
    }

    void setSignals(std::shared_ptr<QDialog> form) {
        QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
        QObject::connect(form.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
        QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus,QString)),this,SLOT(setStatus(UI::FormStatus, QString)));
    }


public:
    explicit FormStatusHandler(QApplication &app, QObject *parent = nullptr): _app{app} {
        this->setParent(parent);
        onload();

    }

    FormStatus getStatus() const {
        if (this->status.isEmpty() && this->mainWindowOpen)
            return UI::FormStatus::MAIN;
        else if (!this->status.isEmpty()) {
            return this->status.top();
        } else {
            return UI::FormStatus::NULLSTATUS;
        }


    }

    void onload () {

        this->_reg = core::AbstractAssetRegister::instance<AssetRegister>();
        setStatus(LOGIN);
    }



public slots:
    void setStatus(UI::FormStatus stat);
    void setStatus(UI::FormStatus stat, QString id);
    void closeStatus(UI::FormStatus stat = NULLSTATUS);







};
}

#endif // FORMSTATUSHANDLER_H
