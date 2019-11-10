#include "assettype.h"
using namespace core;



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

 /*
AssetType::AssetType( QString id, QObject *parent) {
    this->id = id;
    this->setParent(parent);

}
*/
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
QVector<std::shared_ptr<UserPropertyDefinition>> AssetType::getPropertyDefinitions() {
    return this->propertyDefinitions.values().toVector();
}


QVector<QString> AssetType::getPropertyDefinitionNames() {
    return this->propertyDefinitions.keys().toVector();
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
std::shared_ptr<Asset> AssetType::newInstance(QString id) {

   std::shared_ptr<Asset>a{new Asset(id,std::shared_ptr<AssetType>(this))};
   return a;
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


void AssetType::instanceDestroyed2(std::shared_ptr<RegisteredEntity> instance) {

    auto id = instance->getId();

    for (auto a = this->_instances.begin(); a != this->_instances.end();a++ ) {

        if (a->get()->getId() == id) {
            this->_instances.erase(a);
            break;
        }
    }

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
bool AssetType::setDateTime(QDateTime date){
    this->lastEditTime = date;
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
bool AssetType::setLastEditedBy(QString username) {
    this->lastEditedBy = username;
    return true;
}
/**
 * @brief getId
 * fetches entities id
 * @return
 *  entities id
 */
QString AssetType::getId () {
    return id;
}

QString AssetType::type() {
    return "AssetType";
}


QString AssetType::getLastEditedBy () {
    return this->lastEditedBy;
}
QDateTime AssetType::getDateTime() {
    return this->lastEditTime;
}

void AssetType::instanceDestroyed(QString id) {
    if (!_instances.isEmpty()) {
        int count = 0;
        for (auto i =_instances.begin();i != _instances.end();i++) {

            if (i->get()->getId().compare(id) == 0) {
                _instances.remove(count);
                break;
            }
            count++;
        }

    }
}
