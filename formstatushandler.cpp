#include "formstatushandler.h"
using namespace UI;
void FormStatusHandler::setStatus(FormStatus stat) {
    // check if current status is not equal to new status

    if (this->getStatus() !=  stat) {

        this->status.append(stat);
        this->addDialog(stat);
        showWindow();

    }

}

void FormStatusHandler::setStatus2(UI::FormStatus stat, QString id) {

    if (this->getStatus() !=  stat) {


        this->status.append(stat);
        printStatus();

        printStatus(stat);
        this->addDialog(stat,id);

        printStatus();

         this->printDialog();
    }
}

void FormStatusHandler::printStatus (UI::FormStatus stat) {
    QString debug;
    if (stat == NULLSTATUS) {
    for (auto i : status) {
        if (i == UI::EDITASSET) {
            debug += ",editasset";
        } else if (i == UI::MAIN) {
            debug += ",main";
        } else if (i == UI::LOGIN) {
            debug += ",login";
        } else if (i == UI::EDITCUSTODIAN) {
            debug += ",editCustodian";
        } else if (i == UI::USERPROPERTY) {
            debug += ",Userproperty";
        } else if (i == UI::EDITASSETTYPE) {
            debug += ",editAssettype";
        }
    }

    } else {
        auto i = stat;
        if (i == UI::EDITASSET) {
            debug += ",editasset";
        } else if (i == UI::MAIN) {
            debug += ",main";
        } else if (i == UI::LOGIN) {
            debug += ",login";
        } else if (i == UI::EDITCUSTODIAN) {
            debug += ",editCustodian";
        } else if (i == UI::USERPROPERTY) {
            debug += ",Userproperty";
        } else if (i == UI::EDITASSETTYPE) {
            debug += ",editAssettype";
        }
    }

}

void FormStatusHandler::printDialog() {
    QString debug;

    for (auto a: this->dialogs) {
        if (a == nullptr) {
           debug+= this->_window->windowTitle()+",";
        } else
            debug += a.get()->windowTitle()+",";
    }
}


void FormStatusHandler::closeStatus(FormStatus stat) {
    if (stat == NULLSTATUS) {
        if (dialogs.size() > 1) {
           auto index =  dialogs.size()-1;
           auto dialog = dialogs.top();
           status.pop();
           printStatus();
           printDialog();

           // showWindow();

           this->toBeDeleteddialogs.append(index);
           this->dialogs.top()->hide();

           if (this->mainWindowOpen)
                 this->_window->updateList();

           printStatus();

        } else if (mainWindowOpen == false) {

            this->closeApplication();
        }
    } else {


        auto index = this->status.indexOf(stat);
        if (stat == UI::LOGIN) {
            closeDialog(index);
        } else {
           printStatus(stat);

           auto dialog = this->getDialog(stat);
           if (dialog != nullptr)
                dialog->hide();

        }


        status.remove(index);
        if (this->mainWindowOpen)
              this->_window->updateList();



        if (dialogs.size() == 0 && mainWindowOpen == false) {
            this->closeApplication();
        }
    }
}

std::shared_ptr<QDialog> FormStatusHandler::getDialog(FormStatus stat) {

    QString search = "";
    if (stat == UI::EDITASSET) {
        search = "Asset";
    } else if (stat == UI::EDITASSETTYPE) {
        search = "AssetType";
    } else if (stat == UI::EDITCUSTODIAN) {
        search = "Custodian";
    } else if (stat == UI::USERPROPERTY) {
        search = "UserProperty";
    }


    for (auto a : this->dialogs) {
        if (a != nullptr) {
            if (a.get()->windowTitle().compare(search) == 0) {

                return a;
            }
        }
    }
    return nullptr;
}

void FormStatusHandler::closeDialog(FormStatus stat) {
    this->closeDialog(this->status.indexOf(stat));

}

void FormStatusHandler::closeApplication () {
    QApplication::exit();
}

void FormStatusHandler::setSignals(std::shared_ptr<QDialog> form) {
    QObject::connect(form.get(),SIGNAL(openForm(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
    QObject::connect(form.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
    QObject::connect(form.get(),SIGNAL(openForm2(UI::FormStatus,QString)),this,SLOT(setStatus2(UI::FormStatus, QString)));

}

void FormStatusHandler::onload () {

    this->_reg = core::AbstractAssetRegister::instance<AssetRegister>();
    setStatus(LOGIN);
}


FormStatus FormStatusHandler::getStatus()  {
    if (this->status.isEmpty() && this->mainWindowOpen) {
        return UI::FormStatus::MAIN;
    } else if (!this->status.isEmpty()) {
        printStatus(this->status.top());
        return this->status.last();
    } else {
        return UI::FormStatus::NULLSTATUS;
    }


}
bool FormStatusHandler::closeDialog(int index) {

   if (index != -1 && index <= dialogs.size()) {
        auto form = this->dialogs.at(index);

        if (form == nullptr) {
            this->_window->disconnect();
            this->_window->close();
            this->closeApplication();
        }else {
            form->disconnect();
            form->close();
            this->dialogs.remove(index);
        }
        return true;
    } else {
        return false;
    }
}

void FormStatusHandler::hideWindow(int at) {
    if (dialogs.size()  > at) {

        auto dia = this->dialogs.at(at).get();

        if (dia == nullptr) {


        } else if (!dia->isHidden()) {
            dia->hide();
        }
    }

}

void FormStatusHandler::showWindow() {

    if (this->getStatus() == MAIN) {
        if (this->dialogs.size() > 1) {
            auto dia = this->dialogs.at(this->dialogs.size()-2).get();
            if (!dia->isHidden())
                dia->setVisible(false);
        }
        if (_window->isHidden()) {
            _window->setVisible(true);

        }
        _window->setFocus();


    } else {
        if (this->status.size() > 1) {


            //hideWindow(this->dialogs.size()-2);
        }
        this->dialogs.top()->show();
    }

}

void FormStatusHandler::addDialog (FormStatus stat, QString id) {

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
            this->_window = std::shared_ptr<MainWindow>(new MainWindow(this->_reg));
            this->dialogs.append(nullptr);
            QObject::connect(this->_window.get(),SIGNAL(openForm(UI::FormStatus)),this,SLOT(setStatus(UI::FormStatus)));
            QObject::connect(this->_window.get(),SIGNAL(closeForm(UI::FormStatus)),this,SLOT(closeStatus(UI::FormStatus)));
            QObject::connect(this->_window.get(),SIGNAL(openForm2(UI::FormStatus,QString)),this,SLOT(setStatus2(UI::FormStatus, QString)));
            mainWindowOpen = true;
            showWindow();
            break;
        }

        case FormStatus::EDITASSETTYPE: {
        bool success = false;
        for (auto a : this->dialogs)  {
            if (a != nullptr) {
                if (a->windowTitle().compare("AssetType") == 0) {
                    emit this->sendIdToAssetType(id);
                    a->show();
                    success = true;

                }
            }
        }
        if (success == false) {
            std::shared_ptr<QDialog>form {new AssetTypeForm(_reg,id,_window.get())};
            this->dialogs.append(form);
            this->setSignals(form);
            QObject::connect(this,SIGNAL(sendIdToAssetType(QString)),form.get(),SLOT(recieveId(QString)));
            showWindow();
        }
            break;
        }

    case FormStatus::EDITCUSTODIAN: {

        bool success = false;
        for (auto a : this->dialogs)  {
            if (a != nullptr) {
                if (a->windowTitle().compare("Custodian") == 0) {
                    emit this->sendIdToCustodian(id);
                    a->show();
                    success = true;

                }
            }
        }
        if (success == false) {
            auto form = std::make_shared<CustodianForm>(_reg,id,_window.get());
            form->setAttribute(Qt::WA_DeleteOnClose,true);
            this->dialogs.append(form);
            this->setSignals(form);
            QObject::connect(this,SIGNAL(sendIdToCustodian(QString)),form.get(),SLOT(recieveId(QString)));
            showWindow();
        }
        break;
    }

    case FormStatus::EDITASSET: {
        bool success = false;
        for (auto a : this->dialogs)  {
            if (a != nullptr) {
                if (a->windowTitle().compare("Asset") == 0) {
                    emit this->sendIdToAsset(id);
                    a->show();
                    success = true;

                }
            }
        }
        if (success == false) {
            std::shared_ptr<QDialog>form {new AssetForm(_reg,id,_window.get())};

            this->dialogs.append(form);
            this->setSignals(form);
            QObject::connect(this,SIGNAL(sendIdToAsset(QString)),form.get(),SLOT(recieveId(QString)));
            showWindow();
        }
        break;
    }

    case FormStatus::USERPROPERTY: {
        bool success = false;
        for (auto a : this->dialogs)  {
            if (a != nullptr) {
                if (a->windowTitle().compare("Asset") == 0) {
                    emit this->sendIdToAsset(id);
                    a->show();
                    success = true;

                }
            }
        }
        std::shared_ptr<QDialog>form {new UserPropertyForm(_reg,id,_window.get())};
        this->dialogs.append(form);
        this->setSignals(form);
        showWindow();
        break;
    }
    default:
        break;

    }
}
