#include "assetform.h"
#include "ui_assetform.h"

AssetForm::AssetForm(std::shared_ptr<AbstractAssetRegister>& reg, QString id,QWidget *parent) :
    QDialog(parent),
    _reg(reg),
    _id(id),
    ui(new Ui::AssetForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Asset");
    onload();
}

AssetForm::~AssetForm()
{
    delete ui;
}

void AssetForm::onload () {


    _asset.reset();
    std::shared_ptr<RegisteredEntity> entity(_reg->retrieveEntity(_id));
    _asset = std::dynamic_pointer_cast<Asset>(entity);

    setId();
    this->purchaseDate();
    this->purchasePrice();
    this->model();
    this->brand();
    this->serialNo();
    this->assetType();
    this->custodian();
    this->disposalDate();
    this->lastEditedBy();
    this->lastTimeEdited();

}

void AssetForm::setId() {
    ui->id->setText(_asset->getId());
}

void AssetForm::purchaseDate() {
    ui->PurchaseDate->setDateTime(_asset->getPurchaseDate());

}
void AssetForm::serialNo() {
    ui->SerialNo->setText(_asset->getSerialNo());

}
void AssetForm::brand() {
    ui->Brand->setText(_asset->getBrand());

}
void AssetForm::model() {
    ui->Model->setText(_asset->getModel());

}
void AssetForm::purchasePrice() {
    ui->PurchasePrice->setText(_asset->getPrice().value().toString());

}
void AssetForm::disposalDate() {
     ui->DisposalDate->setDateTime(_asset->getDisposalDate());

}
void AssetForm::assetType() {
   auto list = _reg.get()->allEntities();
   int index = -1;
   if (!list.isEmpty()) {
       for (auto a = list.begin(); a != list.end();a++){
           if (a->get()->type().compare("AssetType") == 0) {
               ui->Assettype->addItem(a->get()->getId(),a->get()->getId());
               if (a->get()->getId() == _asset->getAssetType()->getId())
                    index = ui->Assettype->count() - 1;
           }
       }
    }

   ui->Assettype->setCurrentIndex(index);
}
void AssetForm::lastEditedBy() {
    ui->LastEditedBy->setText(_asset->getLastEditedBy());

}
void AssetForm::lastTimeEdited(){

    ui->lastTimeEdited->setDateTime(_asset->getLastTimeEdited());
}


bool AssetForm::savePurchaseDate() {
    _asset->setDateTime();
    return true;
    
}
bool AssetForm::saveSerialNo() {
    _asset->setSerialNo(ui->SerialNo->text());
    return true;
    
}
bool AssetForm::saveBrand() {
    _asset->setBrand(ui->Brand->text());
    return true;
    
}
bool AssetForm::saveModel() {
    _asset->setModel(ui->Model->text());
    return true;
    
}
bool AssetForm::savePurchasePrice() {
    auto price = _asset->getPrice();
    bool ok;
    double pri = ui->PurchasePrice->text().toDouble(&ok);
    if (ok == false) {
        QMessageBox::warning(this,"Purchase Price Error", "Invalid amount given in purchase price. allowable values: 1, 2.3,2.34");
        return false;
    } else {
        price.setValue(pri);
        _asset->setPurchasePrice(price);
        return true;
    }
    
}
bool AssetForm::saveDisposalDate() {
    _asset->sellAsset(ui->DisposalDate->dateTime());
    return true;
    
}
bool AssetForm::saveAssetType() {
    auto i = this->_reg->retrieveEntity(ui->Assettype->currentText());
    
    if (i != nullptr) {
        _asset->setAssetType(std::dynamic_pointer_cast<AssetType>(i));
        return true;
    } else {
        return false;
    }
}
void AssetForm::saveLastEditedBy() {
    _asset->setLastEditedBy(_reg->username());

    
}
void AssetForm::saveLastTimeEdited() {
    _asset->setDateTime();
}

void AssetForm::custodian() {

    auto list = _reg.get()->allEntities();
    int index = 0;
    if (!list.isEmpty()) {
        for (auto a = list.begin(); a != list.end();a++){
            if (a->get()->type().compare("Custodian") == 0) {
                ui->Custodian->addItem(a->get()->getId());
                if (_asset->getCustodian() != nullptr) {
                    if (a->get()->getId().compare( _asset->getCustodian()->getId()) == 0)
                         index = ui->Custodian->count() - 1;
                }
            }
        }
     }

    ui->Custodian->setCurrentIndex(index);

}

bool AssetForm::saveCustodian() {
    if (_asset->getCustodian()!= nullptr) {
        if (ui->Custodian->currentText().compare(_asset->getCustodian()->getId()) != 0) {
            auto i = this->_reg->retrieveEntity(ui->Custodian->currentText());
            if (i != nullptr) {
                _asset->setCustodian(std::dynamic_pointer_cast<Custodian>(i));
                return true;
            } else {
                return false;
            }
        }

    }else if (ui->Custodian->currentText().compare("")) {
        return true;
    }
   return false;

}
void AssetForm::on_addProperty_button_clicked()
{
    QMessageBox::warning(this,"Unimplemented","This feature was implemented but I was unable to complete error checking in time.");
}

void AssetForm::on_save_button_clicked()
{
    this->saveBrand();
    this->saveModel();
    saveSerialNo();
    saveAssetType();
    saveDisposalDate();
    saveCustodian();
    saveLastEditedBy();
    saveLastTimeEdited();
    on_cancel_button_clicked();

}

void AssetForm::on_cancel_button_clicked()
{
    emit closeForm(UI::EDITASSET);
}

void AssetForm::recieveId(QString id) {

    this->_id = id;
    this->onload();
}
