#ifndef ASSETREGISTER_H
#define ASSETREGISTER_H

#include "abstractassetregister.h"
#include "commonentityfactory.h"
namespace core {
class AssetRegister : public AbstractAssetRegister
{


public:
    AssetRegister();

   /**
    * @brief username
    * tring)accessor and mutator for managing the
    * “logged-in” user. This will just be a simple string
    * (QString since we are in the Qt framework)
    * specified by the user through the GUI. There will not be any control
    * over what users are allowed, permissions, etc. it will only be used
    * to record who created and modified an asset (or related entity) as part of the entity’s meta-data.
    * @return QString
    * username
    */
   QString username() override;
   /**
    * @brief setUsername
    * mutator to set username
    * @return
    * true upon successfully changing username
    * false - failed to change username
    */
   bool setUsername(QString username) override;
   /**
    * @brief generateId
    * assuming we are operating in a distributed environment it is
    * important that we avoid clashes between entity identifiers created
    * by different instances of the application running on different
    * (or the same) computer. A relatively simple way to achieve this
    * is to use randomly generated IDs using an algorithm designed for
    * such systems such as UUIDs (Universally Unique Identifiers).
    * This function will create and return a new UUID (as a QString) to be
    * used as an identifier. This can be done using Qt with the QUuid class
    * and its createUuid() function, then converting it to a string via toString().
    * @return
    * QString generated Identification number as a string
    */
   QString generateId() override;
   /**
    * @brief getFactory
    * returns (a reference to) the AbstractEntityFactory
    * that will be used to create entities to be stored in the register.
    * @return AbstractEntityFactory
    *  get factory
    */
   std::shared_ptr<AbstractEntityFactory> getFactory() override;
   /**
    * @brief storeEntity
    * stores an entity (Asset, AssetType, Custodian) in the Asset Register: must return true if the entity was added successfully, false if the it was not (e.g., due to the ID not being unique).
The type is not specified as this may be defined as a single function using inheritance and polymorphism to a common base class, or multiple function overloads for the concrete types. Document your design decision.
    * @return
    * true - stored entity
    * false - entity id is not unique
    */
   bool storeEntity(std::shared_ptr<RegisteredEntity> entity) override;
   /**
    * @brief retrieveEntity
    * retrieves an entity (Asset, AssetType, Custodian) from the Asset Register using the entity’s identifier.
    * Must return a nullptr if an entity with that identifier cannot be found.
    * As above, may be one function or a group of overloaded functions (would need to be a template function as the signature cannot differ by only return type), document your decision.
    *
    * @param id
    * identification of entity
    * @return
    * Entity - successfully found entity
    * nullptr - could not find entity in list
    */
   std::shared_ptr<RegisteredEntity> retrieveEntity(QString id) override;
   /**
    * @brief deleteEntity
    *
    * @return
    * true - found entity and deleted
    * false - could not find identification
    */
   bool deleteEntity(QString id) override;
   /**
    * @brief allEntities
    * remove the entity with the given identifier from the register:
    * must return true if the entity was removed,
    * false if it was not (e.g., it may have already been removed).
    * Calling this function multiple times with the same identifier will
    * not have any negative consequences. Make sure you clear any dynamically
    * allocated memory when deleting an entity from the register (refer to QObject::deleteLater() when cleaning up QObjects).
    * @return
    * vector array of entities
    */
   QVector<std::shared_ptr<RegisteredEntity>> allEntities() override;
   /**
    * @brief persist
    * stores the data maintained in the register to some
    * form of persistent storage. The actual type of
    * storage and the expected key/value pairs stored
    * in the options map (e.g., a filename) are implementation
    * specific. Not all types of AbstractAssetRegister support
    * persistence but many do or are likely to. Returns true if
    * the data is successfully persisted.
    * @param options
    *
    * @return
    */
   bool persist(QMap<QString, QVariant> options) override;
   /**
    * @brief restore
    * loads the data from persistent storage into the register.
    * The actual type of storage and the expected key/value pairs stored
    * in the options map (e.g., a filename) are implementation specific.
    * Not all types of AbstractAssetRegister support persistence but many
    * do or are likely to. Returns true if the data is successfully restored.
    * @param options
    * @return
    */
   bool restore(QMap<QString, QVariant> options) override;



   static void resetSingleton();


};

}

#endif // ASSETREGISTER_H
