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

    this->id = id;
    this->setParent(parent);

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
bool AssetType::addPropertyDefinition (QString name,std::shared_ptr<UserPropertyDefinition> propertyDefinition) {
    if ( this->propertyDefinitions.contains(name) )
        return false;
    else {

        this->propertyDefinitions.insert(name,propertyDefinition);
        return true;
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
bool AssetType::updatePropertyDefintion (QString name,std::shared_ptr<UserPropertyDefinition> propertyDefinition) {
    if (this->propertyDefinitions.contains(name)) {
        this->propertyDefinitions.remove(name);
        this->propertyDefinitions.insert(name,propertyDefinition);
        return true;
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
        return true;
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
QVector<std::shared_ptr<UserPropertyDefinition>> AssetType::getPropertyDefinition() {
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
std::shared_ptr<UserPropertyDefinition> AssetType::getPropertyDefintion(QString name) {
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
std::shared_ptr<Asset> AssetType::newInstance() {

 std::shared_ptr<Asset>a{new Asset(QString("sdnf"),std::shared_ptr<RegisteredEntity>(this))};

}
/**
 * @brief instances
 * gets all asset instances connected to this asset type
 * @return
 * vector, array of assets
 */
QVector<std::shared_ptr<Asset>> AssetType::instances () {
    return this->_instances;
}


void AssetType::instanceDestroyed(std::shared_ptr<Asset> instance) {
    auto id = instance->getId();

    for (auto a = this->_instances.begin(); a != this->_instances.end();a++ ) {

        if (a->get()->getId() == id) {
            this->_instances.erase(a);
            break;
        }
    }

}
