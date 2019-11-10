#include "userpropertyform.h"
#include "ui_userpropertyform.h"

UserPropertyForm::UserPropertyForm(std::shared_ptr<AbstractAssetRegister> reg, QString id,QWidget *parent) :
    QDialog(parent),
    _reg(reg),
    _id(id),
    ui(new Ui::UserPropertyForm)
{
    ui->setupUi(this);
    std::shared_ptr<RegisteredEntity> entity(_reg->retrieveEntity(id));

    
    if (entity->type().compare("Asset") == 0) {
        _asset.reset(dynamic_cast<Asset *>(entity.get()));
        this->_def.reset(new UserPropertyDefinition(_reg->generateId(),_asset.get()));
        status = statuses::ASSET;
    } else if (entity->type().compare("AssetType") == 0) {
        _assetType.reset(dynamic_cast<AssetType *>(entity.get()));
        this->_def.reset(new UserPropertyDefinition(_reg->generateId(),_assetType.get()));
        status = statuses::ASSETTYPE;
    }

}

UserPropertyForm::~UserPropertyForm()
{
    delete ui;
}

void UserPropertyForm::on_validator_currentIndexChanged(const QString &arg1)
{
    if (arg1.compare("Custom") == 0){
        addCustomValidator();
    } else if (arg1.compare("Minimum") == 0) {
        addMinimumValidator();
    }else if (arg1.compare("Maximum") == 0) {
        addMaximumValidator();
    }else if (arg1.compare("Phone Number") == 0) {
        addPhoneValidator();
    } else if (arg1.compare("Department") == 0) {
        addDepartmentValidator();
    }
}


void UserPropertyForm::addPhoneValidator() {
    if (!this->_def->validatorExists("Phone")){
        _currentValidator.reset(new PhoneNumberValidator());
        successfullyAddedValidator();
    } else {
        QMessageBox::warning (this,"Error","Phone validator already exists.");
    }



}
void UserPropertyForm::addDepartmentValidator() {
    if (!this->_def->validatorExists("Department")) {
        _currentValidator.reset(new DepartmentValidator());
    } else {
        QMessageBox::warning (this,"Error","Department validator already exists.");
    }
}
void UserPropertyForm::addCustomValidator() {
    QVector<QString> values;
    while (QMessageBox::question(this,"Add Another?","Would you like to add another value?",QMessageBox::Yes | QMessageBox::No)) {

        QString reply = QInputDialog::getText(this,"Custom Value","Input Custom Value:",QLineEdit::Normal);
        values.append(reply);

    }
    _currentValidator.reset(new ValueListValidator(values));


}
void UserPropertyForm::addMaximumValidator() {

    if (this->_def->validatorExists("Maximum")) {
        QMessageBox::warning (this,"Error","Maximum Value validator already exists.");
    } else {
        auto reply = QInputDialog::getText(this,"Maximum Value","Input Maximum Value",QLineEdit::Normal,"");
        bool ok;
        int val = reply.toInt(&ok);
        if (reply.size() == 0 || ok == false) {
            QMessageBox::warning(this,"Error","Invalid Value inputted.");
        } else {
           this->_currentValidator.reset(new MaximumValueValidator(val,this));

        }
    }


}
void UserPropertyForm::addMinimumValidator() {

    if (this->_def->validatorExists("Minimum")) {
        QMessageBox::warning (this,"Error","Maximum Value validator already exists.");
    } else {
        auto reply = QInputDialog::getText(this,"Minimum Value","Input minimum Value",QLineEdit::Normal,"");
        bool ok;
        int val = reply.toInt(&ok);
        if (reply.size() == 0 || ok == false) {
            QMessageBox::warning(this,"Error","Invalid Value inputted.");
        } else  {
            _currentValidator.reset(new MinimumValueValidator(val));
        }
    }
}

void UserPropertyForm::successfullyAddedValidator() {
    QMessageBox::information(this,"Success","Successfully added validator");
}


void UserPropertyForm::saveValue() {
     this->_def->setValue(ui->value->text());

    if (status == ASSET) {
        this->_userProperty.reset(new TypedUserProperty<QString>(_reg->generateId(),this->_def));
        this->_asset->addUserProperty(ui->name->text(),this->_userProperty);
    } else if (status == ASSETTYPE) {
        this->_assetType->addPropertyDefinition(ui->name->text(),this->_def);
    }
}

void UserPropertyForm::on_AddProperty_button_clicked()
{
    this->saveValue();
    closeForm(UI::USERPROPERTY);
}

void UserPropertyForm::on_cancel_button_clicked()
{
    closeForm(UI::USERPROPERTY);
}

void UserPropertyForm::on_addValidator_button_clicked()
{
   QString text =  ui->validator->currentText();
   QString name = text;
   if (text.compare("custom") == 0) {
       int count = 0;
       while (this->_def->validatorExists("Custom"+QString(count))) {
           count++;
       }
       name = "Custom"+QString(count);
   } else if (this->_def->validatorExists(text)) {
       QMessageBox::warning(this,"Error",text+" validator already exists.");
   } else {
    this->_def->addValidator(name,this->_currentValidator);
    this->successfullyAddedValidator();
   }
}
