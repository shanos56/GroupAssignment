#ifndef FORMSTATUS_H
#define FORMSTATUS_H
#include <QString>

namespace UI {

enum FormStatus {LOGIN,MAIN,LOADFILE,VIEWASSETS,EDITCUSTODIAN,EDITASSETTYPE,EDITASSET,USERPROPERTY, NULLSTATUS};

QString departments[] = {"Logistics","Maintenance","Operations"};


}
#endif // FORMSTATUS_H
