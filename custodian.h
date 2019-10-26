#ifndef CUSTODIAN_H
#define CUSTODIAN_H
#include "registeredentity.h"
#include "typeduserproperty.h"
#include <QVariant>

namespace core {
class Custodian : public RegisteredEntity
{


    /**
     * @brief lastEditTime
     * a timestamp (QDateTime) that indicates when the last modification was made to the entity;
     * it is used common meta-data in database applications used for various purposes including
     * synchronisation and integrity checks. MUST be updated whenever a change is made to the entity.
     */
    QDateTime lastEditTime;

    /**
     * @brief lastEditedBy
     * the name of the logged in user (from the register) who changed the entity last;
     * this is common meta-data in database applications and used for integrity checking,
     * prevenance, and auditing purposes. MUST be updated whenever a change is made to the entity.
     */
    QString lastEditedBy;
    /**
    * everybody needs a name. You MAY reuse the standard 'objectName' of QObjects, rather than declaring a new data member.
    *
    *
    */
    QString name;

    /**
     * @brief department
     * A UserProperty of type QString that restricts the allowable
     * values to the following: "Maintenance", "Operations", "Logistics"
     */
    TypedUserProperty <QString> department;
    /**
     * @brief phoneNumber
     * A UserProperty of type QString that restricts the allowable values to (mostly) valid phone numbers. The constraints are as follows:
     *
     *   8-11 digits (inclusive)
     *   optional '+' at the beginning (and only the beginning)
     *   Spaces are allowed
     *   No other characters are all allowed
     *   This allows values such as: 83026611, 8302 6611, 08 8302 6611, +61 8 8302 6611
     *   But NOT: 8302, 8302 6611 12345, 61+ 8 8302 6611, ext. 25000
     */
    TypedUserProperty <QString> phoneNumber;

public:
    Custodian(QString id);

    /**
     * @brief Custodian
     * since the class is derived from QObject,
     * it should have the common QObject constructor for specifying the parent
     * object to support Qt's object hierarchy; however,
     * it also needs a unique identifier to be provided as all registered entities require an identifier.
     * @param id
     * identification of custodian
     * @param parent
     * parent of custodian
     */
    Custodian( QString id, QObject *parent);

    /*
     * Mutators and accessors
     *
     * */

    /**
     * @brief setPhoneNumber
     * @return
     * true - successfully set phone number
     * false - invalid phone number
     */
    bool setPhoneNumber (TypedUserProperty<QString>);
    /**
     * @brief getPhoneNumber
     * gets phone number of user or custodian
     * @return
     * userproperty string containing phone number
     */
    TypedUserProperty<QString> getPhoneNumber();

    /**
     * @brief setName
     * sets the name of the user
     * @return
     * true - valid name set to custodian
     * false - invalid name
     */
    bool setName(TypedUserProperty<QString>);
    /**
     * @brief getName
     * gets name of custodian
     * @return
     * name of custodian
     */
    QString getName();

    /**
     * @brief setDepartment
     * sets users departments
     * values to the following: "Maintenance", "Operations", "Logistics"
     * @return
     * true - valid department set to custodian
     * false - invalid department
     */
    bool setDepartment(TypedUserProperty<QString>);




    /**
     * @brief getDepartment
     *
     * @return
     *
     */
    TypedUserProperty<QString> getDepartment ();
    /**
       * @brief setDateTime
       * sets the latest date time
       * @param date
       * date to set otherwise use current date
       * @return
       * true - successfully set date time
       * false - invalid datetime
       */

    bool setDateTime(QDateTime date = QDateTime::currentDateTime()) override;

    /**
       * @brief setLastEditedBy
       * set the last time user was edited
       * @param username
       * name of last user
       * @return
       * true - successfully set user
       * false - invalid user
       */
    bool setLastEditedBy(QString username) override;

    /**
     * @brief getId
     * fetches identification number
     * @return
     * id of custodian
     */
    QString getId() override;

    /**
     * @brief getDateTime
     * gets date time
     * @return
     * QDateTime
     */
    QDateTime getDateTime();



};
}

#endif // CUSTODIAN_H
