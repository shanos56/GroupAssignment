#include "custodianform.h"
#include "ui_custodianform.h"

CustodianForm::CustodianForm(std::shared_ptr<AbstractAssetRegister> reg, QString id,QWidget *parent) :
    QDialog(parent),
    _reg{reg},
    _id{id},
    ui(new Ui::CustodianForm)

{
    ui->setupUi(this);
    custodian = std::shared_ptr<Custodian>(dynamic_cast<Custodian *>(_reg->retrieveEntity(_id).get()));
}

CustodianForm::~CustodianForm()
{
    delete ui;
}


void CustodianForm::setPhoneNumber () {
    ui->phonenumber->clear();
    ui->phonenumber->insert(custodian->getPhoneNumber()->getValue());

}
void CustodianForm::setId() {
    ui->id->clear();
    ui->id->setText(custodian->getId());

}
void CustodianForm::setName() {
    ui->Name->clear();
    ui->Name->setText(custodian->getName());

}
void CustodianForm::setDepartment() {
    ui->department->clear();
    int index = 0;
    for (QString i : UI::departments) {
        ui->department->addItem(i,i);

    }

    if ((index = ui->department->findText(custodian->getDepartment()->getValue())) != -1) {
        ui->department->setCurrentIndex(index);
    }


}
void CustodianForm::setLastTimeEdited() {

    ui->lastTimeEdited->clear();

    ui->lastTimeEdited->setDateTime(custodian->getDateTime());


}
void CustodianForm::setLastEditedBy() {

    ui->LastEditedBy->clear();
    ui->LastEditedBy->setText(custodian->getLastEditedBy());
}


bool CustodianForm::savePhoneNumber() {

    std::shared_ptr<UserPropertyDefinition> definit (new UserPropertyDefinition(_reg->generateId(),custodian.get()));

    definit->addValidator("Phone",std::shared_ptr<UserPropertyValidator>(new PhoneNumberValidator ()));
    std::shared_ptr<TypedUserProperty<QString>> phone(new  TypedUserProperty<QString>(_reg->generateId(),definit));

    phone->setValue(ui->phonenumber->text());

    connect(phone.get(),SIGNAL(validationFailed(QString)),this,SLOT(validationFailed(QString)));

    if (phone->validate()) {
        custodian->setDepartment(phone);
        return true;
    } else {
        return false;
    }

}
bool CustodianForm::saveName() {

     std::shared_ptr<UserPropertyDefinition> definit (new UserPropertyDefinition(_reg->generateId(),custodian.get()));

    std::shared_ptr<TypedUserProperty<QString>> prop(new TypedUserProperty<QString>(_reg->generateId(),definit));
    custodian->setName(prop);

    return true;
}

bool CustodianForm::savelastEditedBy() {
    custodian->setLastEditedBy(_reg->username());
    return true;
}
bool CustodianForm::saveDepartment() {

    std::shared_ptr<UserPropertyDefinition> definit (new UserPropertyDefinition(_reg->generateId(),custodian.get()));

    definit->addValidator("Phone",std::shared_ptr<UserPropertyValidator>(new DepartmentValidator ()));
     std::shared_ptr<TypedUserProperty<QString>> department(new  TypedUserProperty<QString>(_reg->generateId(),definit));

    department->setValue(ui->department->currentText());

    if (department->validate()) {
        custodian->setDepartment(department);
        return true;
    } else {
        return false;
    }
}
bool CustodianForm::saveLastTimeEdited() {

    custodian->setDateTime(ui->lastTimeEdited->dateTime());
    return true;
}




void CustodianForm::on_save_button_clicked()
{
    if (!saveName()) {
        return;
    } else if (!saveDepartment()) {
        return;
    } else if (!savePhoneNumber()) {
        return;
    } else if (!saveLastTimeEdited()) {
        return;
    }

    savelastEditedBy();
    emit closeForm(UI::EDITCUSTODIAN);


}

void CustodianForm::on_cancel_button_clicked()
{

    emit closeForm(UI::EDITCUSTODIAN);

}

void CustodianForm::validationFailed(QString error) {
    QMessageBox::warning(this,"Error",error);
}
