#include "userpropertydefinition.h"
#include "typeduserproperty.h"

using namespace core;
UserPropertyDefinition::UserPropertyDefinition(QString id, QObject *parent) : QObject(parent)
{
this->id = id;
}


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
UserPropertyDefinition::UserPropertyDefinition( QString name, types type, QObject *parent) {
    this->name = name;
    dataType = type;
    this->setParent(parent);

}

QString UserPropertyDefinition::getName () {
    return name;
}

UserPropertyDefinition::types UserPropertyDefinition::getType () {
    return dataType;
}

/**
 * @brief newProperty
 * creates and returns a new UserProperty of an appropriate concrete type associated with this
 * UserPropertyDefinition: optionally with the specified QObject as parent.
 * (This can be used for both user properties of Asset and the data members such as 'phoneNumber' of Custodian).
 * @param parent
 *
 * @return
 */
std::shared_ptr<UserProperty> UserPropertyDefinition::newProperty(QObject *parent) {

    std::shared_ptr<UserPropertyDefinition>th (this);

    if (dataType == types::Qstring) {
        return std::shared_ptr<UserProperty>{new TypedUserProperty<QString>(th)};
    } else if (dataType == types::Int)
        return std::shared_ptr<UserProperty>{new TypedUserProperty<int>(th)};
    else if (dataType == types::Double)
        return std::shared_ptr<UserProperty>{new TypedUserProperty<double>(th)};
    else {
        return nullptr;
    }


}
/**
 * @brief validate
 * validate whether the given property’s value is correct with respect to the this definition's
 * validators: returns the tuple (true, "" ) if validation is successful, and the tuple
 * (false, <failure message>) if any of he validators do not pass.
 * @param property
 * property to add to
 * @note validator only takes references
 * @return
 * success - tuple (true, "" )
 * failure - tuple (false, <failure message>)
 */
std::tuple<bool, QString> UserPropertyDefinition::validate( UserProperty& property) {

    if (!validators.isEmpty()) {
        for (auto i : validators.values()) {
            if (!i->operator()(property))
                return std::make_tuple(false,i->failureMessage(property));
        }
    }
    QString a  = "";

    auto tu = std::tuple(true,a);
    return tu;
}

bool UserPropertyDefinition::addValidator (QString name, std::shared_ptr<UserPropertyValidator> validator) {

    if (validators.contains(name))
        return false;
    else {
        validators.insert(name,validator);
        return true;
    }
    /*
    auto a = this->validators.keys();
    for (auto b = a.begin(); b < a.end();b++) {
        if (b->compare(name) == 0)
            return false;
    }
    validators.insert(name,validator);
    return true;
    */
}

bool UserPropertyDefinition::removeValidator(QString name) {

    if (validators.contains(name)) {
        validators.remove(name);
        return true;
    }
    return false;

}

int UserPropertyDefinition::getPrecision () {
    if (dataType == types::Double)
        return this->doublePrecision;
    else {
        return 0;
    }
}

QString UserPropertyDefinition::getId() {
    return id;
}


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
bool UserPropertyDefinition::setValue (QVariant value) {
    this->_default = value;
    return true;
}
/**
 * @brief getValue
 *   retrieves value
 * @return
 * value to be returned
 */
QVariant UserPropertyDefinition::getValue() {
    return _default;
}


bool UserPropertyDefinition::validatorExists(QString name) {

    if (this->validators.find(name) != this->validators.end()) {
        return true;
    } else {
        return false;
    }
}
