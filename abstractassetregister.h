#ifndef ABSTRACASSETREGISTER_H
#define ABSTRACASSETREGISTER_H

#include <QObject>
#include <QVector>
#include "abstractentityfactory.h"
namespace core {

class AbstractAssetRegister : public QObject
{



    Q_OBJECT

protected:

    QString _username;
    /**
     * @brief _instance
     * instance of AssetRegister
     */
    static std::shared_ptr<AbstractAssetRegister> _instance;

    template<class T>
    static T type;


    /**
     * @brief _entityFactory
     * pointer to abstract entity factory
     */
    std::shared_ptr<AbstractEntityFactory> _entityFactory;
    /**
     * @brief _entities
     * list of entities stored in asset Register
     */
    QVector<std::shared_ptr<RegisteredEntity>> _entities;

     explicit AbstractAssetRegister(QObject *parent = nullptr);
    /**
      * @brief getRegister
      * the register instance. Must be able to support polymorphism.
      * To support the extensibility requirement this member must be protected.
      * This will allow the creation of a MockAssetRegister class for testing.
      * Such a special subclass should have static member function that can clear the register class variable,
      *  allowing a new register object to be created on the subsequent call to instance().
      *
      * @return
      */
     static std::shared_ptr<AbstractAssetRegister> getRegister();
public:

     /**
     * @brief instance
     * returns the single instance of this class (or any of its subclasses). Use lazy initialisation to create the single instance if one does not currently exist. To support extensibility, this is a template function: the type parameter will specify the concrete subclass to instantiate if an instance does not already exist). Once an instance of a type has been created, that instance will always be returned, regardless if the function is called with a different type: i.e., there cannot be multiple register instances of different types instantiated at the same time.
For example, to select the simple AssetRegister class as the singleton, the first call to this function should be: AbstractAssetRegister::instance<AssetRegister>()
Everywhere else in the application may simply call: AbstractAssetRegister::instance<AbstractAssetRegister>()
     * @return
     * returns instance
     */
     template<class T>
     static std::shared_ptr<T> instance();

     template<class T>
     static void setType(T type);


     template<class T>
     static T getType();

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
    virtual QString username() = 0;
    /**
     * @brief setUsername
     * mutator to set username
     * @return
     * true upon successfully changing username
     * false - failed to change username
     */
    virtual bool setUsername(QString) = 0;
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
    virtual QString generateId() = 0;
    /**
     * @brief getFactory
     * returns (a reference to) the AbstractEntityFactory
     * that will be used to create entities to be stored in the register.
     * @return AbstractEntityFactory
     *  get factory
     */
    virtual std::shared_ptr<AbstractEntityFactory> getFactory() = 0;
    /**
     * @brief storeEntity
     * stores an entity (Asset, AssetType, Custodian) in the Asset Register: must return true if the entity was added successfully, false if the it was not (e.g., due to the ID not being unique).
The type is not specified as this may be defined as a single function using inheritance and polymorphism to a common base class, or multiple function overloads for the concrete types. Document your design decision.
     * @return
     * true - stored entity
     * false - entity id is not unique
     */
    virtual bool storeEntity(RegisteredEntity *) = 0;
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
    virtual std::shared_ptr<RegisteredEntity> retrieveEntity(QString id)  = 0;
    /**
     * @brief deleteEntity
     *
     * @return
     * true - found entity and deleted
     * false - could not find identification
     */
    virtual bool deleteEntity(QString id) = 0;
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
    virtual QVector<std::shared_ptr<RegisteredEntity>> allEntities() = 0;
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
    virtual bool persist(QMap<QString, QVariant> options) = 0;
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
    virtual bool restore(QMap<QString, QVariant> options) = 0;



    static void resetSingleton();




signals:

public slots:
};
}

#endif // ABSTRACASSETREGISTER_H
