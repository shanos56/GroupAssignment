#include "assettypeform.h"
#include "ui_assettypeform.h"

AssetTypeForm::AssetTypeForm(std::shared_ptr<AbstractAssetRegister> reg, QString id, QWidget *parent) :
    QDialog(parent),
    _reg(reg),
    _id(id),
    ui(new Ui::AssetTypeForm)
{
    ui->setupUi(this);
    this->setWindowTitle("AssetType");
    onload();
}

void AssetTypeForm::onload () {

    _assetType.reset();

    _assetType = std::dynamic_pointer_cast<AssetType>(_reg->retrieveEntity(_id));
    this->setId();
    this->setLastEditedBy();
    this->setLastTimeEdited();
    this->setPropertyDefinitions();
    this->setAssets();
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

    if (!instances.isEmpty()) {
        for (auto i : instances) {
            ui->assets->addItem(i->getId(),QVariant(i->getId()));
        }
    }
}

void AssetTypeForm::setPropertyDefinitions() {

     ui->definitions->clear();
    auto instances = this->_assetType->getPropertyDefinitions();
    auto names = this->_assetType->getPropertyDefinitionNames();
    int count = 0;
    if (!instances.isEmpty()) {
        for (auto i : instances) {
            ui->definitions->addItem(names.at(count),QVariant(i->getId()));
            count++;
        }
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
    this->_asset.reset();
    _asset = _asset = _reg->getFactory()->createAsset(_assetType,id);
    _reg->storeEntity(_asset);
    emit openForm2(UI::EDITASSET,id);
}

void AssetTypeForm::on_deleteAsset_button_clicked()
{
   auto id = ui->assets->currentData().toString();

   _reg->deleteEntity(id);

   this->setAssets();
}

void AssetTypeForm::on_addDefinition_button_clicked()
{
    QMessageBox::warning(this,"Unimplemented","This feature was implemented but I was unable to complete error checking in time.");
    /*auto id = ui->definitions->currentData().toString();
    emit openForm2(UI::USERPROPERTY,id);*/

}

void AssetTypeForm::on_deleteDefinition_button_clicked()
{
    auto name = ui->definitions->currentText();

    this->_assetType->removePropertyDefinition(name);

}

void AssetTypeForm::on_save_button_clicked()
{
    this->saveLastEditedBy();
    this->setLastTimeEdited();
    closeForm(UI::EDITASSETTYPE);
}


void AssetTypeForm:: recieveId(QString id) {
    this->_id = id;
    this->onload();
}

void AssetTypeForm::on_cancel_button_clicked()
{
    closeForm(UI::EDITASSETTYPE);
}
