#include "assettypeform.h"
#include "ui_assettypeform.h"

AssetTypeForm::AssetTypeForm(std::shared_ptr<AbstractAssetRegister> reg, QString id, QWidget *parent) :
    QDialog(parent),
    _reg(reg),
    _id(id),
    ui(new Ui::AssetTypeForm)
{
    ui->setupUi(this);

    std::shared_ptr<RegisteredEntity> entity(_reg->retrieveEntity(id));

    if (entity != nullptr && entity->type().compare("AssetType") == 0) {
        _assetType.reset(dynamic_cast<AssetType *>(entity.get()));
    } else {
        QMessageBox::warning(this,"Error", "Invalid entity given. Either does not exist or is not asset.");
        emit closeForm(UI::EDITASSET);
    }
}

AssetTypeForm::~AssetTypeForm()
{
    delete ui;
}

void AssetTypeForm::setId() {

    ui->id->setText(this->_assetType->getId());
}


void AssetTypeForm::setLastEditedBy() {
    ui->LastEditedBy->clear();
    ui->LastEditedBy->setText(_assetType->getLastEditedBy());
}

void AssetTypeForm::setLastTimeEdited() {
    ui->lastTimeEdited->clear();

    ui->lastTimeEdited->setDateTime(_assetType->getDateTime());
    
}

void AssetTypeForm::setAssets() {

    ui->assets->clear();
    auto instances = this->_assetType->instances();

    for (auto i : instances) {
        ui->assets->addItem(i.get()->getBrand()+" - "+i.get()->getModel(),QVariant(i->getId()));
    }
}

void AssetTypeForm::setPropertyDefinitions() {

     ui->definitions->clear();
    auto instances = this->_assetType->getPropertyDefinitions();
    auto names = this->_assetType->getPropertyDefinitionNames();
    int count = 0;
    for (auto i : instances) {
        ui->definitions->addItem(names.at(count),QVariant(i->getId()));
        count++;
    }
    
}

void AssetTypeForm::saveLastEditedBy() {
    this->_assetType->setLastEditedBy(_reg->username());
}

void AssetTypeForm::saveLastTimeEdited() {
    this->_assetType->setDateTime();
}

void AssetTypeForm::on_addAsset_button_clicked()
{
    QString id = _reg->generateId();

    _reg->storeEntity(_assetType.get()->newInstance(id));

    emit openForm(UI::EDITASSET,id);
}

void AssetTypeForm::on_deleteAsset_button_clicked()
{
   auto id = ui->assets->currentData().toString();

   _reg->deleteEntity(id);

}

void AssetTypeForm::on_addDefinition_button_clicked()
{
    auto id = ui->definitions->currentData().toString();
    emit openForm(UI::USERPROPERTY,id);

}

void AssetTypeForm::on_deleteDefinition_button_clicked()
{
    auto name = ui->definitions->currentText();

    this->_assetType->removePropertyDefinition(name);

}
