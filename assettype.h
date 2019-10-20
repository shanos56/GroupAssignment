#ifndef ASSETTYPE_H
#define ASSETTYPE_H
#include <QVector>
#include "registeredentity.h"

#include "asset.h"
namespace core {
/**
 * @brief The AssetType class
 *
 *
 */
class AssetType : public RegisteredEntity
{


    /**
     * @brief instances
     * the collection of Asset objects that are the instances of this AssetType.
     * Each Asset of the collection must refer back to the AssetType
     * itself (this is the more important association as the collection of
     * instances can always be inferred from the back-references). This is a
     * composition relation; therefore, destroying the AssetType should destroy all of its instances.
     * You MAY make use of the standard QObject hierarchy to implement this; however, there must still
     * be an accessor called instances() that returns only Asset objects (as opposed to all QObjects).
     */
    QVector<Asset> _instances;

    /**
     * @brief propertyDefinitions
     * a collection of UserPropertyDefinitions that describe the properties specific to the type.
     * This is what allows individual assets to have more specific properties as well as validate the values of
     * those properties (the validators are attached to the UserPropertyDefinitions, not the UserProperties themselves).
     * The properties are managed by name, i.e., there can be only one UserPropertyDefinition with a given
     * name at any one time. This can be handled easily using a QMap object.
     * This data member MUST be properly encapsulated, i.e., the accessor retrieving the entire collection will return a
     * QVector to which modifications will not affect the AssetType. T
     * here should also be an accessor that allows the retrieval of a specific
     * UserPropertyDefinition by name, and mutators that allow the addition or update of a
     * UserPropertyDefinition by passing in the definition object, and the removal of an object by passing in the name.
     */
    QMap<QString,UserPropertyDefinition> propertyDefinitions;


public:
    AssetType();

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
    AssetType( QString id, QObject *parent);

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
    bool addPropertyDefinition (QString name,UserPropertyDefinition propertyDefinition);

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
    bool updatePropertyDefintion (QString name,UserPropertyDefinition propertyDefinition);
    /**
     * @brief removePropertyDefinition
     * deletes a property definition
     * @return
     * true - successfully deleted property definition
     * false - property definition name doesn't exist
     */
    bool removePropertyDefinition (QString name);
    /**
     * @brief getPropertyDefinition
     * fetches all property definitions
     * @return
     * vector(array) of property definitions
     */
    QVector<UserPropertyDefinition> getPropertyDefinition();

    /**
     * @brief getPropertyDefintion
     * copy of defintion
     * @param name
     * name of defintion
     * @return
     * property defintion
     * nullptr
     */
    UserPropertyDefintion getPropertyDefintion(QString name);
    /**
     * @brief newInstance
     * Creates and returns new Asset object that is linked to this AssetType as one of its instances.
     * @return
     */
    Asset newInstance();
    /**
     * @brief instances
     * gets all asset instances connected to this asset type
     * @return
     * vector, array of assets
     */
    QVector<Asset> instances ();

public slots:
    /**
     * @brief instanceDestroyed
     * supports notification of an Asset instance being destroyed.
     * This may result in the update of the instances collection,
     * if not handled by the standard Qt object hierarchy.
     * Note: this slot should still be called even if the standard Qt
     * object hierarchy is being used as it is specific to Asset objects,
     * rather than all QObject children. Remember: QObjects emit the QObject::destroyed
     * signal when they are being deleted.
     * @param instance
     */
    void instanceDestroyed( Asset  instance);


};
}
#endif // ASSETTYPE_H
