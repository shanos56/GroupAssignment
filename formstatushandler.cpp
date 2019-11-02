#include "formstatushandler.h"
using namespace UI;
void FormStatusHandler::setStatus(FormStatus stat) {
    // check if current status is not equal to new status
     qDebug()<<"Add "<< QString(stat);
    if (this->getStatus() !=  stat) {
        qDebug()<<"current status "<< QString(this->getStatus());
        this->status.append(stat);

        qDebug()<<"append dialog status "<< QString(this->getStatus());
        this->addDialog(stat);
        qDebug()<<"append dialog "<< QString(this->getStatus());
        qDebug()<<"Add Window";
        showWindow();
        qDebug()<<"show Window";
    }

}


void FormStatusHandler::closeStatus(FormStatus stat) {
    if (stat == NULLSTATUS) {
        if (dialogs.size() > 1) {
           auto dialog =  dialogs.pop();
           status.pop();
           dialog.get()->close();
        } else if (mainWindowOpen == false) {
            _app.exit();
        }
    } else {

        auto index = status.indexOf(stat);
        closeDialog(index);

        if (dialogs.size() == 0 && mainWindowOpen == false) {
            this->closeApplication();
        }

    }

}
