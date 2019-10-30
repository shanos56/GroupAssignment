#ifndef ABSTRACTENTITYFACTORY_H
#define ABSTRACTENTITYFACTORY_H

#include <QObject>
#include "assettype.h"
#include "userpropertydefinition.h"
#include "asset.h"

namespace core {
class AbstractEntityFactory
{

public:
     virtual ~AbstractEntityFactory();
     AbstractEntityFactory();


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
    virtual std::shared_ptr<Custodian> createCustodian( QString id, QMap <QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr )=0;
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
    virtual std::shared_ptr<AssetType> createAssetType( QString id, QMap <QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) = 0;

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
    virtual std::shared_ptr<Asset> createAsset( std::shared_ptr<AssetType> assetType, QString id, QMap <QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) = 0;
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
    virtual std::shared_ptr<UserPropertyDefinition> createPropertyDefinition( QString id, QMap<QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) = 0;

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

    virtual std::shared_ptr<UserProperty> createProperty( std::shared_ptr<UserPropertyDefinition> definition, QString id, QMap <QString, QVariant> parameters = QMap<QString, QVariant>{}, QObject *parent = nullptr ) = 0;

    signals:

public slots:
};
}

#endif // ABSTRACTENTITYFACTORY_H
