#include "custodian.h"
using namespace core;

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
Custodian::Custodian( QString id, QObject *parent) {
    this->id = id;
    this->setParent(parent);
}

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
bool Custodian::setPhoneNumber (std::shared_ptr<TypedUserProperty <QString>> number) {

    if (number->validate())  {
        this->phoneNumber = number;
         return true;
    }
   return false;
}
/**
 * @brief getPhoneNumber
 * gets phone number of user or custodian
 * @return
 * userproperty string containing phone number
 */
std::shared_ptr<TypedUserProperty <QString>> Custodian::getPhoneNumber() {
    return this->phoneNumber;
}

/**
 * @brief setName
 * sets the name of the user
 * @return
 * true - valid name set to custodian
 * false - invalid name
 */
bool Custodian::setName(std::shared_ptr<TypedUserProperty <QString>> name) {
    if (name->validate()) {
        this->name = name->getValue();
        return true;
    }else {
        return false;
    }

}
/**
 * @brief getName
 * gets name of custodian
 * @return
 * name of custodian
 */
QString Custodian::getName() {
    return this->name;
}

/**
 * @brief setDepartment
 * sets users departments
 * values to the following: "Maintenance", "Operations", "Logistics"
 * @return
 * true - valid department set to custodian
 * false - invalid department
 */
bool Custodian::setDepartment(std::shared_ptr<TypedUserProperty <QString>> department) {
    this->department = department;
    return true;
}
/**
 * @brief getDepartment
 *
 * @return
 *
 */
std::shared_ptr<TypedUserProperty <QString>> Custodian::getDepartment () {
    return department;
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

bool Custodian::setDateTime(QDateTime date) {

    this->lastEditTime = date;
    return true;
}

QDateTime Custodian::getDateTime() {
    return this->lastEditTime;
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
bool Custodian::setLastEditedBy(QString username) {
    this->lastEditedBy = username;
    return true;

}

QString Custodian::getId() {
    return this->id;
}

QString Custodian::type() {
    return "Custodian";
}

QString Custodian::getLastEditedBy () {
    return this->lastEditedBy;
}
