#include "assetform.h"
#include "ui_assetform.h"

AssetForm::AssetForm(std::shared_ptr<AbstractAssetRegister> reg, QString id,QWidget *parent) :
    QDialog(parent),
    _reg(reg),
    _id(id),
    ui(new Ui::AssetForm)
{
    ui->setupUi(this);

    std::shared_ptr<RegisteredEntity> entity(_reg->retrieveEntity(id));

    if (entity != nullptr && entity->type().compare("Asset") == 0) {
        _asset.reset(dynamic_cast<Asset *>(entity.get()));
    } else {
        QMessageBox::warning(this,"Error", "Invalid entity given. Either does not exist or is not asset.");
        emit closeForm(UI::EDITASSET);
    }
}

AssetForm::~AssetForm()
{
    delete ui;
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
    auto i = this->_reg->retrieveEntity(ui->Assettype->currentData().toString());
    
    if (i != nullptr) {
        _asset->setAssetType(i);
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
    int index = -1;
    if (!list.isEmpty()) {
        for (auto a = list.begin(); a != list.end();a++){
            if (a->get()->type().compare("Custodian") == 0) {
                std::shared_ptr<Custodian> cus(dynamic_cast<Custodian *>(a->get()));
                ui->Custodian->addItem(cus->getName(),a->get()->getId());
                if (a->get()->getId().compare( _asset->getCustodian()->getId()) == 0)
                     index = ui->Custodian->count() - 1;
            }
        }
     }

    ui->Custodian->setCurrentIndex(index);

}

bool AssetForm::saveCustodian() {
    if (ui->Custodian->currentData().toString().compare(_asset->getCustodian()->getId()) != 0) {
        auto i = this->_reg->retrieveEntity(ui->Custodian->currentData().toString());

        if (i != nullptr) {
            _asset->setCustodian(std::shared_ptr<Custodian>(dynamic_cast<Custodian *>(i.get())));
            return true;
        } else {
            return false;
        }
    }
    return true;

}
void AssetForm::on_addProperty_button_clicked()
{
    emit openForm(UI::USERPROPERTY,this->_id);
}

void AssetForm::on_save_button_clicked()
{

    if (this->saveBrand() && this->saveModel() && saveSerialNo() && saveAssetType() && saveCustodian() && saveDisposalDate())  {
        saveLastEditedBy();
        saveLastTimeEdited();
        emit closeForm(UI::EDITASSET);
    }

}

void AssetForm::on_cancel_button_clicked()
{
    emit closeForm(UI::EDITASSET);
}
