#include "assettype.h"
using namespace core;
AssetType::AssetType()
{

}


/**
 * @brief AssetType
 * since the class is derived from QObject,
 * it should have the common QObject constructor for specifying the parent
 * object to support Qt's object hierarchy; however, it also needs a unique
 * identifier to be provided as all registered entities require an identifier.
 * @param id
 * identification of asset
 * @param parent
 * parent object
 */
AssetType::AssetType( QString id, QObject *parent) {

}

/**
 * @brief addPropertyDefinition
 * sets a new property definition
 * @param name
 * name of property definition
 * @param propertyDefinition
 * property definition to create
 * @return
 * true - successfully added property definition
 * false - property definition name already exists
 */
bool AssetType::addPropertyDefinition (QString name,UserPropertyDefinition propertyDefinition) {
    if ( this->propertyDefinitions.contains(name) )
        return false;
    else {

        this->propertyDefinitions.insert(name,propertyDefinition);
    }
}

/**
 * @brief updatePropertyDefinition
 * updates a property definition
 * @param name
 * name of property definition
 * @param propertyDefinition
 * property definition to update
 * @return
 * true - successfully updated property definition
 * false - property definition name already exists
 */
bool AssetType::updatePropertyDefintion (QString name,UserPropertyDefinition propertyDefinition) {
    if (this->propertyDefinitions.contains(name)) {
        this->propertyDefinitions.remove(name);
        this->propertyDefinitions.insert(name,propertyDefinition);
    } else {
        return false;
    }


}
/**
 * @brief removePropertyDefinition
 * deletes a property definition
 * @return
 * true - successfully deleted property definition
 * false - property definition name doesn't exist
 */
bool AssetType::removePropertyDefinition (QString name) {
    if (this->propertyDefinitions.contains(name)) {
        this->propertyDefinitions.remove(name);
    } else {
        return false;
    }
}
/**
 * @brief getPropertyDefinition
 * fetches all property definitions
 * @return
 * vector(array) of property definitions
 */
QVector<UserPropertyDefinition> AssetType::getPropertyDefinition() {
    return this->propertyDefinitions.values().toVector();
}

/**
 * @brief getPropertyDefintion
 * copy of defintion
 * @param name
 * name of defintion
 * @return
 * property defintion
 * nullptr
 */
UserPropertyDefinition AssetType::getPropertyDefintion(QString name) {
    if (this->propertyDefinitions.contains(name))
        return this->propertyDefinitions.find(name).value();
    else {
        return nullptr;
    }

}
/**
 * @brief newInstance
 * Creates and returns new Asset object that is linked to this AssetType as one of its instances.
 * @return
 */
Asset AssetType::newInstance() {

    Asset a ("aa",this);



}
/**
 * @brief instances
 * gets all asset instances connected to this asset type
 * @return
 * vector, array of assets
 */
QVector<Asset> AssetType::instances () {

}
