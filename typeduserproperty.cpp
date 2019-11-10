#include "typeduserproperty.h"
#include <QDebug>

using namespace core;


template <class T>
TypedUserProperty<T>::TypedUserProperty(TypedUserProperty &t) {
    this->id = t.id;
    this->name = t.name;
    this->_value = t._value;
    this->definition = t.definition;

}

template <class T>
TypedUserProperty<T> TypedUserProperty<T>::operator=(TypedUserProperty &t) {
    return TypedUserProperty<T>(t);

}
template <class T>
TypedUserProperty<T>::TypedUserProperty(std::shared_ptr<UserPropertyDefinition> definition){

    this->definition = definition;
}

template <class T>
TypedUserProperty<T>::TypedUserProperty(QString id, std::shared_ptr<UserPropertyDefinition> definition){
    this->id = id;
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


    if constexpr(std::is_same<T,int>::value == true) {
        emit valueChanged(this->_value,val);
        this->_value = val.toInt();
    } else if constexpr(std::is_same<T,QString>::value == true) {
        emit valueChanged(this->_value,val);
        this->_value = val.toString();
    } else if constexpr(std::is_same<T,double>::value == true){
        emit valueChanged(this->_value,val);
        this->_value = val.toDouble();
    }


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
        emit this->validationFailed(std::get<1>(res));
        return false;
    }
}

template <class T>
QString TypedUserProperty<T>::getId() {
    return id;

}




