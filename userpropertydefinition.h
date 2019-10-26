#ifndef USERPROPERTYDEFINITION_H
#define USERPROPERTYDEFINITION_H

#include <QObject>
#include <QString>
#include <QVariant>
#include "userpropertyvalidator.h"

namespace core {
class UserPropertyDefinition : public QObject
{

    /**
     * @brief precision
     * precision of a double value
     */
    int doublePrecision = 4;

    /**
     * @brief type
     * the type of the property defined by an enumeration of allowable types.
     * You must support at least the following data types: int, double, and string
     * (actual values will be QString objects for compaitiblity with the rest of the Qt application).
     * The type MUST be read-only.
     */
    enum types {Qstring,Int,Double};
    /**
     * @brief dataType
     * type this class holds
     */
    types dataType;

    /**
     * @brief name
     * 	the name of the property; each UserProperty of a UserPropertyDefinition
     *  will have the same name. Only one property with the same name can occur in an Asset/AssetType at one time,
     * i.e., adding a UserPropertyDefinition to an AssetType using a name that is already present must do nohting
     * (use updateProperty to replace a property with the same name). The name MUST be read-only.
     */
    QString name;

    /**
     * @brief _default
     * the default value for this UserPropertyDefinition: stored as a QVariant (see https://doc.qt.io/qt-5/qvariant.html)
     * which allows values of different types to be stored consistently and converted between types if necessary.
     */
    QVariant _default;
    /**
     * @brief validators
     * a collection of UserPropertyValidators that will be used to ensure that the property values are correct.
     * Validators are managed by name (refer to UserPropertyValidators section)
     * and MUST be able to be added, removed, and (possibly) accessed.
     */
    QMap<QString,std::shared_ptr<UserPropertyValidator>> validators;

    QString id;



Q_OBJECT
public:
    explicit UserPropertyDefinition(QString id,QObject *parent = nullptr);

    UserPropertyDefinition(UserPropertyDefinition &);


    /**
     * @brief getPrecision
     * gets precision of double type
     * @return
     * > 0 - precision of double
     * 0 - not a double type
     */
    int getPrecision();
    /**
     * @brief UserPropertyDefinition
     * since the class is derived from QObject,
     * it should have the common QObject constructor for specifying the parent object to support Qt's object hierarchy;
     * however, it also requires additoinal fields for the read-only data members.
     * @param name
     * name of property
     * @param type
     * type of property
     * @param parent
     * parent of object
     */
    UserPropertyDefinition( QString name, types type, QObject *parent = nullptr);

    /**
    * @brief getName
    * fetches the name of userDefinition
    * @return
    * name
    */
   QString getName();
   /**
    * @brief getType
    * gets type of user definition property
    * @return
    * returns type of user definition property
    */
   types getType ();
   /**
    * @brief setValidator
    * @param name
    * @param validator
    * @return
    */
   bool addValidator (QString name, std::shared_ptr<UserPropertyValidator> validator);
   /**
    * @brief removeValidator
    * removes validator from list
    * @param name
    * name of validator
    * @return
    * true- successfully removed validator
    * false - unsuccessfully removed validator
    */
   bool removeValidator(QString name);
   /**
    * @brief getId
    * fetches id
    * @return
    * gets id of object
    */
   QString getId();
   /**
    * @brief setValue
    * @param value
    * @return
    * true - successfully set value
    * false - failed to set value
    */
   bool setValue (QVariant value);
   /**
    * @brief getValue
    *   retrieves value
    * @return
    * value to be returned
    */
   QVariant getValue();

signals:

public slots:
    /**
     * @brief newProperty
     * creates and returns a new UserProperty of an appropriate concrete type associated with this
     * UserPropertyDefinition: optionally with the specified QObject as parent.
     * (This can be used for both user properties of Asset and the data members such as 'phoneNumber' of Custodian).
     * @param parent
     *
     * @return
     * new user property
     */
    std::shared_ptr<UserProperty> newProperty(QObject *parent = nullptr);

    /**
     * @brief validate
     * validate whether the given property’s value is correct with respect to the this definition's
     * validators: returns the tuple (true, "" ) if validation is successful, and the tuple
     * (false, <failure message>) if any of he validators do not pass.
     * @param property
     * property to add to
     * @return
     * success - tuple (true, "" )
     * failure - tuple (false, <failure message>)
     */
    std::tuple<bool, QString> validate( std::shared_ptr<UserProperty> property);
};

}

#endif // USERPROPERTYDEFINITION_H
