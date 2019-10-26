#ifndef ASSET_H
#define ASSET_H

#include "registeredentity.h"

#include "custodian.h"
#include "typeduserproperty.h"
#include "userproperty.h"
#include <QVariant>

namespace core {
class Asset : public RegisteredEntity
{

    Q_OBJECT

    /**
     * @brief type
     * a reference (not necessarily a C++ reference) to the AssetType of this Asset.
     * This MAY be implemented through the standard QObject object hierarchy;
     * however, there must be an accessor type() that returns an AssetType rather than QObject.
     * @note an id would be a good way to indicate the type of asset
     */
    std::shared_ptr<RegisteredEntity> assetType;

    /**
     * @brief serialNo
     * an identifier typically written on the object, its serial number.
     * This is not the same as its ‘id’ (inherited from RegisteredEntity),
     * which is an internal system identifier for keeping track of the object in the system.
     * It is entirely possible for two assets of different types to have the same serialNo.
     */
    QString serialNo;
    /**
     * @brief brand
     * the maker of the asset, e.g., “ACME Pumps Co.”
     */
    QString brand;
    /**
     * @brief model
     * the specific model of the Asset.
     * While many assets may be of the same type (e.g., Pump, Computer, etc.),
     * they may be of different models (e.g., ‘ACME Co. Pump X3000’)
     */
    QString model;
    /**
     * @brief purchasePrice
     * the cost of the asset when it was bought (as a UserProperty of type double with a precision of 2, refer to the UserPropertyDefinition class).
     */
    TypedUserProperty<double> purchasePrice;

    /**
     * @brief purchaseDate
     * the date at which the asset was bought by the company
     */
    QDateTime purchaseDate;
    /**
     * @brief disposalDate
     * the date at which the asset of disposed of (sold, thrown away, etc.)
     * by the company. If an asset is not yet disposed it will no value for disposalDate;
     * in contrast to purchase date which will always have a value as Assets in the AssetRegister
     * are those that have been purchased by the company. Disposed Assets cannot change Custodian.
     */
    QDateTime disposalDate;
    /**
     * @brief custodian
     * a reference (not necessarily a C++ reference) to a Custodian object.
     * Note the cardinality of exactly 1 is from the user's perspective,
     * i.e., at a conceptual level.
     * That is, the user interface must not allow an Asset to be stored or saved if it has no Custodian;
     * however, enforcing such a constraint at the lowest-level in the code is not always possible nor useful.
     * For example, if having a Custodian was enforced through a constructor, you would not be able to create
     * an Asset object until a Custodian had been determined. It can be useful, however, to be able to create
     * an object without a Custodian and update the value once it has been determined.
     * @note an id would be a good choice
     */
    std::shared_ptr<Custodian> custodian;

    /**
     * @brief userProperties
     */
    std::map<QString,std::shared_ptr<UserProperty>> userProperties;


public:
    /**
     * @brief Asset
     * since the class is derived from QObject, it should have the common QObject constructor
     * for specifying the parent object to support Qt's object hierarchy; however,
     * it also needs a unique identifier to be provided as all registered entities require an identifier.
     * @param id
     * identification of asset
     * @param parent
     * parent
     */
    explicit Asset( QString id, QObject *parent);

    Asset( QString id, std::shared_ptr<RegisteredEntity>);

    /**
     * @brief purchaseAsset
     * sets purchase asset date
     * @param time
     * time the asset was purchased
     */
    bool purchaseAsset (QDateTime time);
    /**
     * @brief getPurchaseDate
     * fetches purchase date from parameters
     * @return
     * purchase date
     */
    QDateTime getPurchaseDate();
    /**
     * @brief setPurchasePrice
     * purchase price of asset
     * @param price
     * price of asset
     */
    bool setPurchasePrice(TypedUserProperty<double> price);
    /**
     * @brief getPrice
     * fetches the price of asset
     * @return
     * price of asset
     */
    TypedUserProperty<double> getPrice();
    /**
     * @brief setModel
     * sets model brand to asset
     * @param model
     * model of asset
     */
    bool setModel(QString model);
    /**
     * @brief getModel
     * fetches model of asset
     * @return
     * model of asset
     */
    QString getModel();

    /**
     * @brief setBrand
     * sets brand name of asset
     * @param name
     * name of brand
     */
    bool setBrand (QString  name);
    /**
     * @brief getBrand
     * fetches brand of asset
     * @return
     * brand name
     */
    QString getBrand();
    /**
     * @brief sellAsset
     * if asset is sold sell the asset
     * @param time
     * date of sale of asset
     */
    bool sellAsset(QDateTime time);

    /**
     * @brief getDisposalDate
     * fetches disposal date
     * @return
     * date time when disposal took place
     */
    QDateTime getDisposalDate();

    /**
     * @brief setSerialNo
     * sets serial number of asset
     * @param serial
     * serial number of asset
     */
    bool setSerialNo(QString serial);
    /**
     * @brief getSerialNo
     * fetches serial number of asset
     * @return
     * string containing serial number
     */
    QString getSerialNo();
    /**
     * @brief getAssetType
     * fetches the asset type this asset belongs too
     * @return
     * asset type pointer
     */
    std::shared_ptr<RegisteredEntity> getAssetType();
    /**
     * @brief setAssetType
     * sets asset type of
     * @param type
     * asset type
     * @return
     * successfully set asset type
     */
    bool setAssetType(std::shared_ptr<RegisteredEntity> type);


    bool setCustodian(std::shared_ptr<Custodian> custodian);

    std::shared_ptr<Custodian> getCustodian();

    bool addUserProperty(QString name,std::shared_ptr<UserProperty> property);

    std::shared_ptr<UserProperty> getUserProperty(QString name);

    /**
       * @brief setDateTime
       * sets the latest date time
       * @param date
       * date to set otherwise use current date
       * @return
       * true - successfully set date time
       * false - invalid datetime
       */
      bool setDateTime(QDateTime date = QDateTime::currentDateTime());
    /**
       * @brief setLastEditedBy
       * set the last time user was edited
       * @param username
       * name of last user
       * @return
       * true - successfully set user
       * false - invalid user
       */
      bool setLastEditedBy(QString username);
    /**
     * @brief getId
     * fetches entities id
     * @return
     *  entities id
     */
   QString getId ();



public slots:
    /**
     * @brief userPropertyChanged
     * allows notifications of changes to the value of the user properties (including 'purchasePrice').
     * The object that emitted the signal can be retrieved inside the function definition through a call
     * to the sender() function. This may be used to ensure the inherited meta-data is updated as required.
     * @param newValue
     * @param oldValue
     */
    void userPropertyChanged( QVariant newValue, QVariant oldValue);


};
}

#endif // ASSET_H
