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


    void addDialog (FormStatus stat) {

        switch (stat) {

            case LOGIN: {
            qDebug()<<"Login";
                std::shared_ptr<QDialog>form {new Login(_reg,_window.get())};
                qDebug()<<"created Login";
                this->dialogs.append(form);
                 qDebug()<<"appended Login";
                QObject::connect(form.get(),SIGNAL(loginSuccess(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
                QObject::connect(form.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
                qDebug()<<"Added Login";
                showWindow();
                break;
            }

            case MAIN: {
                this->_window = std::shared_ptr<QMainWindow>(new MainWindow());
                qDebug() << "Main App created";
                this->dialogs.append(nullptr);
                mainWindowOpen = true;
                break;
            }

            case FormStatus::VIEWASSETTYPES: {


            }

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
    void closeStatus(UI::FormStatus stat = NULLSTATUS);







};
}

#endif // FORMSTATUSHANDLER_H
