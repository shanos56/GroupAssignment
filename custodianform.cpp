#include "custodianform.h"
#include "ui_custodianform.h"

CustodianForm::CustodianForm(std::shared_ptr<AbstractAssetRegister>& reg, QString id,QWidget *parent) :
    QDialog(parent),
    _reg{reg},
    _id{id},
    ui(new Ui::CustodianForm)

{
    ui->setupUi(this);


    this->setWindowTitle("Custodian");
     this->setValues(id);
}

CustodianForm::~CustodianForm()
{
    delete ui;
}


void CustodianForm::setPhoneNumber () {
    ui->phonenumber->clear();
    if (custodian->getPhoneNumber() != nullptr)
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
    QString dep = "";
    if (custodian->getDepartment() != nullptr){
        dep = custodian->getDepartment()->getValue();
    }

    for (QString i : UI::departments) {
        ui->department->addItem(i,i);

    }
    if (dep.compare("") != 0) {
        ui->department->setCurrentText(dep);
    } else {
        ui->department->setCurrentIndex(0);
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


    phone->setValue(QString(ui->phonenumber->text()));


    if (phone->validate()) {

        custodian->setPhoneNumber(phone);
        return true;
    } else {
        QMessageBox::warning(this,"Phone Error",phone->getErrorMessage());
        return false;
    }

}
bool CustodianForm::saveName() {

    if (ui->Name->text().compare("") == 0) {
            QMessageBox::warning(this,"Name Error","A Custodian requires a name");
            return false;
    }

    auto  definit = std::make_shared<UserPropertyDefinition> (_reg->generateId(),custodian.get());

    auto  prop = std::make_shared<TypedUserProperty<QString> >(_reg->generateId(),definit);

    prop->setValue(QString(ui->Name->text()));

    if (custodian->setName(prop) ) {
        return true;
    }
        return false;

}

bool CustodianForm::savelastEditedBy() {
    custodian->setLastEditedBy(_reg->username());
    return true;
}
bool CustodianForm::saveDepartment() {

    std::shared_ptr<UserPropertyDefinition> definit (new UserPropertyDefinition(_reg->generateId(),custodian.get()));

    definit->addValidator("Department",std::shared_ptr<UserPropertyValidator>(new DepartmentValidator ()));
     std::shared_ptr<TypedUserProperty<QString>> department(new  TypedUserProperty<QString>(_reg->generateId(),definit));


     department->setValue(QString(ui->department->currentText()));

    if (department->validate()) {
        custodian->setDepartment(department);
        return true;
    } else {
        QMessageBox::warning(this,"Department Error",department->getErrorMessage());
        return false;
    }

}
bool CustodianForm::saveLastTimeEdited() {

    custodian->setDateTime();
    return true;
}



void CustodianForm::on_save_button_clicked()
{


    if (!this->saveName()){
        return;
    } else if (!saveDepartment()) {
        return;
    } else if (!savePhoneNumber()) {
        return;
    } else if (!saveLastTimeEdited()) {
        return;
    }

    savelastEditedBy();
    on_cancel_button_clicked();


}

void CustodianForm::setValues(QString id) {

    this->_id = id;
    custodian.reset();
    custodian = std::dynamic_pointer_cast<Custodian>(_reg->retrieveEntity(_id));
    this->setId();
    this->setName();
    this->setDepartment();
    this->setPhoneNumber();
    this->setLastEditedBy();
    this->setLastTimeEdited();
}

void CustodianForm::on_cancel_button_clicked()
{

    emit closeForm(UI::EDITCUSTODIAN);

}

void CustodianForm::validationFailed(QString error) {
    QMessageBox::warning(this,"Error",error);
}

void CustodianForm::recieveId(QString id) {

    this->setValues(id);
}
