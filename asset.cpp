#include "asset.h"
#include "abstractassetregister.h"
using namespace core;

Asset::Asset(QString id, QObject *parent)
{
    this->id = id;

}


Asset::Asset(QObject *parent)
{


}

Asset::Asset(QString id, std::shared_ptr<RegisteredEntity> assetType) {
    this->id = id;
    this->assetType = assetType;
}


void Asset::purchaseAsset (QDateTime time) {

    this->purchaseDate = time;
}
QDateTime Asset::getPurchaseDate() {

    return this->purchaseDate;
}

void Asset::setPurchasePrice(TypedUserProperty<double> price){
    this->purchasePrice = price;

}
TypedUserProperty<double> Asset::getPrice(){
    return purchasePrice;
}

void Asset::setModel(QString model){
    this->model = model;
}
QString Asset::getModel(){
    return model;
}

void Asset::setBrand (QString  name){
    this->brand = name;
}
QString Asset::getBrand(){
    return this->brand;
}

void Asset::sellAsset(QDateTime time){
    this->disposalDate = time;

}
QDateTime Asset::getDisposalDate(){
    return disposalDate;
}


void Asset::setSerialNo(QString serial){
    this->serialNo = serial;

}
QString Asset::getSerialNo(){
    return this->serialNo;
}

std::shared_ptr<RegisteredEntity> Asset::getAssetType(){
     return this->assetType;

}
bool Asset::setAssetType(std::shared_ptr<RegisteredEntity> type){
    this->assetType = type;
}

void Asset::setCustodian(std::shared_ptr<Custodian> custodian){
    this->custodian = custodian;

}
std::shared_ptr<Custodian> Asset::getCustodian(){
    return this->custodian;
}

void Asset::addUserProperty(QString name,std::shared_ptr<UserProperty> property){
    this->userProperties.insert(std::pair<QString,std::shared_ptr<UserProperty>>(name,property));
}

std::shared_ptr<UserProperty> Asset::getUserProperty(QString name){
    auto it = this->userProperties.find(name);
    if (it != this->userProperties.end()) {
        return it->second;
    }else {
        return nullptr;
    }
}
