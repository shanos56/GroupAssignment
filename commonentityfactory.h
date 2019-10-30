#ifndef COMMONENTITYFACTORY_H
#define COMMONENTITYFACTORY_H

#include "abstractentityfactory.h"

namespace core{
class CommonEntityFactory : public AbstractEntityFactory
{
public:
    CommonEntityFactory();


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
    std::shared_ptr<Custodian> createCustodian( QString id, QMap <QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) override;
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
    std::shared_ptr<AssetType> createAssetType( QString id, QMap <QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) override;

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
    std::shared_ptr<Asset> createAsset( std::shared_ptr<AssetType> assetType, QString id, QMap <QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) override;
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
    std::shared_ptr<UserPropertyDefinition> createPropertyDefinition( QString id, QMap<QString, QVariant> parameters = QMap <QString,QVariant>{}, QObject *parent = nullptr ) override;

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
    std::shared_ptr<UserProperty> createProperty( std::shared_ptr<UserPropertyDefinition> definition, QString id, QMap <QString, QVariant> parameters = QMap<QString, QVariant>{}, QObject *parent = nullptr ) override;

};
}
#endif // COMMONENTITYFACTORY_H
