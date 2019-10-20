#include "typeduserproperty.h"
using namespace core;
template <class T>
TypedUserProperty<T>::TypedUserProperty(std::shared_ptr<UserPropertyDefinition> definition){

    this->definition = definition;
}



/**
 * @brief getValue
 * value of property
 * @return
 * value of property
 */
template <class T>
QVariant TypedUserProperty<T>::value() {

    return QVariant::fromValue(this->_value);
}
 /**
  * @brief getValue
  * gets value of class
  * @return
  * value
  */
template <class T>
T TypedUserProperty<T>::getValue() {
    return _value;

}


 /**
  * @brief setValue
  * set value to property
  * @param val
  * value to set to property
  * @return
  * true - successfully set value
  * false - invalid value
  */
template<class T>
void TypedUserProperty<T>::setValue(QVariant val) {
    if (std::is_same<T,int>::value)
        _value = val.toInt();
    else if (std::is_same<T,QString>::value)
        _value = val.toString();
    else if (std::is_same<T,double>::value)
        _value = val.toDouble();

}

template <class T>
QString TypedUserProperty<T>::getName () {
    return name;
}

template <class T>
void TypedUserProperty<T>::setName (QString name) {
    this->name = name;
}


 /**
  * @brief setValue
  * do not set value
  * @param val
  * value to set
  */
template <class T>
void TypedUserProperty<T>::setValue (T val) {
    _value = val;
}
 /**
  * @brief validate
  * checks if a valid property
  * @return
  */
template <class T>
bool TypedUserProperty<T>::validate() {
    std::tuple<bool,QString> res = this->definition.get()->validate(std::shared_ptr<TypedUserProperty>(this));

    if (std::get<0>(res) == true)
        return true;
    else {
        return false;
    }
}

