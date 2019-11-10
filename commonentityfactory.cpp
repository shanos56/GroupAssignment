#include "commonentityfactory.h"
using namespace core;
CommonEntityFactory::CommonEntityFactory(){

}




/**
  @brief
  Instantiates and returns a (pointer to a)
    Custodian object with the given id,
    optional parameters, and optionally a parent QObject.
    The QMap parameter MAY contain values for the attributes of Custodian,
    such as "department" = "Maintenance",
    or any other values deemed necessary to correctly construct the object.

    @param id
    identification string of custodian
    @param paramaters map of parameters for custodian
    @param parent pointer to parent of custodian

**/
std::shared_ptr<Custodian> CommonEntityFactory::createCustodian( QString id, QMap <QString, QVariant> parameters, QObject *parent) {

    std::shared_ptr<Custodian> custodian {new core::Custodian(id,parent)};

    for (auto i = parameters.begin(); i != parameters.end(); i++) {
         if (i.key().compare("DateTime") == 0) {
            custodian.get()->setDateTime(i.value().toDateTime());
        } else if (i.key().compare("LastEditedBy") == 0) {
            custodian.get()->setLastEditedBy(i.value().toString());
        }
    }

    return custodian;

}

/**

  @brief
  Instantiates and returns an (pointer to an) AssetType object with the given id,
    optional parameters, and optionally a parent QObject.
    The QMap parameter MAY contain values deemed necessary
    to correctly construct the object.
    @param id
    identification string of AssetType
    @param paramaters optional map of parameters for AssetType
    @param parent optional pointer to parent of AssetType
  */
std::shared_ptr<AssetType> CommonEntityFactory::createAssetType( QString id, QMap <QString, QVariant> parameters, QObject *parent){

    std::shared_ptr<AssetType> assetType {new AssetType(id,parent)};

    for (auto i = parameters.begin(); i != parameters.end(); i++) {
         if (i.key().compare("DateTime") == 0) {
            assetType.get()->setDateTime(i.value().toDateTime());
         } else if (i.key().compare("lastEditedBy") == 0) {
             assetType.get()->setLastEditedBy(i.value().toString());
         }
    }

    return assetType;
}

/**

  @brief
    Instantiates and returns an (pointer to an)
    Asset object of the specified AssetType and with the given id,
    optional parameters, and optionally a parent QObject.
    The QMap parameter MAY contain values for the attributes of Asset,
    such as "serialNo" = "12345-XXX-64",
    or any other values deemed necessary to correctly construct the object.
    @param id
    identification string of Asset
    @param paramaters optional map of parameters for Asset
    @param parent optional pointer to parent of Asset
  */
std::shared_ptr<Asset> CommonEntityFactory::createAsset( std::shared_ptr<AssetType> type, QString id, QMap <QString, QVariant> parameters, QObject *parent){

    std::shared_ptr<Asset> a {new Asset(id,parent)};
    a->setAssetType(type);
    for (auto it = parameters.begin(); it != parameters.end() ; it++) {
        if (it.key().compare("Username") == 0)
            a.get()->setLastEditedBy(it.value().toString());
        else if (it.key().compare("PurchaseDate") == 0)
             a.get()->setDateTime(it.value().toDateTime());
        else if (it.key().compare("Model") == 0) {
            a.get()->setModel(it.value().toString());
        }else if (it.key().compare("Brand") == 0) {
            a->setBrand(it.value().toString());
        }else if (it.key().compare("Model") == 0)
            a->setModel(it.value().toString());
    }
    return a;

}
/**
  @brief
  Instantiates and returns a (pointer to a)
UserPropertyDefinition object with the given id,
optional parameters, and optionally a parent QObject.
The QMap parameter MAY contain values for the attributes of UserPropertyDefinition,
such as "default" = 1, or any other values deemed necessary to correctly
construct the object.
    @param id
    identification string of UserPropertyDefinition
    @param paramaters [optional] map of parameters for UserPropertyDefinition
    @param parent [optional] pointer to parent of UserPropertyDefinition
*/
std::shared_ptr<UserPropertyDefinition> CommonEntityFactory::createPropertyDefinition( QString id, QMap<QString, QVariant> parameters, QObject *parent) {
    std::shared_ptr<UserPropertyDefinition> a(new UserPropertyDefinition(id, parent));
    for (auto it = parameters.begin(); it != parameters.end() ; it++) {
        if (it.key().compare("default") == 0)
            a.get()->setValue(it.value());
    }
    return a;
}

/**
  @brief
Instantiates and returns a (pointer to a)
UserProperty object of the specified UserPropertyDefinition
and with the given id, optional parameters, and optionally a
parent QObject. The QMap parameter MAY contain values for the
attributes of UserProperty, such as "value" = "the value", or any
other values deemed necessary to correctly construct the object.
    @param id
    identification string of UserProperty
    @param paramaters [optional] map of parameters for UserProperty
    @param parent [optional] pointer to parent of UserProperty
*/

std::shared_ptr<UserProperty> CommonEntityFactory::createProperty( std::shared_ptr<UserPropertyDefinition> definition, QString id, QMap <QString, QVariant> parameters, QObject *parent){
    auto it = parameters.find("type");
    std::shared_ptr<UserProperty> a(new TypedUserProperty<QString>(id,definition));
    QString type = "QString";
    if (it != parameters.end()) {
        if (it.value().toString().compare("Double") == 0) {
            type = "Double";
            std::shared_ptr<UserProperty> a {new TypedUserProperty<double>(id,definition)};
        } else if (it.value().toString().compare("Int") == 0) {
            type = "Int";
            std::shared_ptr<UserProperty> a {new TypedUserProperty<int>(id,definition)};
        }
    }
    for (auto it = parameters.begin(); it != parameters.end();it++) {
        if (it.key().compare("value") == 0){
             a->setValue(it.value());
        }
    }
    return a;
}
