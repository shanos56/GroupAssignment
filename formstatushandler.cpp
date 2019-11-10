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

void FormStatusHandler::setStatus(UI::FormStatus stat, QString id) {

    if (this->getStatus() !=  stat) {
        this->status.append(stat);
        this->addDialog(stat);
        showWindow();
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
