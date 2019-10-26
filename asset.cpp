#include "asset.h"
#include "abstractassetregister.h"
using namespace core;

Asset::Asset(QString id, QObject *parent)
{
    this->id = id;
    this->setParent(parent);


}



Asset::Asset(QString id, std::shared_ptr<RegisteredEntity> assetType) {
    this->id = id;
    this->assetType = assetType;
}


bool Asset::purchaseAsset (QDateTime time) {
    this->purchaseDate = time;
}
QDateTime Asset::getPurchaseDate() {

    return this->purchaseDate;
}

bool Asset::setPurchasePrice(TypedUserProperty<double> price){
    this->purchasePrice = price;
    return true;

}
TypedUserProperty<double> Asset::getPrice(){
    return purchasePrice;
}

bool Asset::setModel(QString model){
    this->model = model;
    return true;
}
QString Asset::getModel(){
    return model;
}

bool Asset::setBrand (QString  name){
    this->brand = name;
    return true;
}
QString Asset::getBrand(){
    return this->brand;
}

bool Asset::sellAsset(QDateTime time){
    this->disposalDate = time;
    return true;

}
QDateTime Asset::getDisposalDate(){
    return disposalDate;
}


bool Asset::setSerialNo(QString serial){
    this->serialNo = serial;
    return true;

}
QString Asset::getSerialNo(){
    return this->serialNo;
}

std::shared_ptr<RegisteredEntity> Asset::getAssetType(){
     return this->assetType;

}
bool Asset::setAssetType(std::shared_ptr<RegisteredEntity> type){
    this->assetType = type;
    return true;
}

bool Asset::setCustodian(std::shared_ptr<Custodian> custodian){
    this->custodian = custodian;
    return true;

}
std::shared_ptr<Custodian> Asset::getCustodian(){
    return this->custodian;
}

bool Asset::addUserProperty(QString name,std::shared_ptr<UserProperty> property){
    auto pair = this->userProperties.insert(std::pair<QString,std::shared_ptr<UserProperty>>(name,property));

    return pair.second;
}

std::shared_ptr<UserProperty> Asset::getUserProperty(QString name){
    auto it = this->userProperties.find(name);
    if (it != this->userProperties.end()) {
        return it->second;
    }else {
        return nullptr;
    }
}

void Asset::userPropertyChanged(QVariant newValue, QVariant oldValue){

}

/**
   * @brief setDateTime
   * sets the latest date time
   * @param date
   * date to set otherwise use current date
   * @return
   * true - successfully set date time
   * false - invalid datetime
   */
bool Asset::setDateTime(QDateTime date) {
    this->purchaseDate = date;
    return true;
}
/**
   * @brief setLastEditedBy
   * set the last time user was edited
   * @param username
   * name of last user
   * @return
   * true - successfully set user
   * false - invalid user
   */
bool Asset::setLastEditedBy(QString username) {
    this->lastEditedBy = username;
    return true;
}
/**
 * @brief getId
 * fetches entities id
 * @return
 *  entities id
 */
QString Asset::getId () {
    return id;
}

