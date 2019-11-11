#ifndef TYPEDUSERPROPERTY_H
#define TYPEDUSERPROPERTY_H
#include "userpropertydefinition.h"
#include "userproperty.h"
#include <tuple>

namespace core {

/**
 *
 * The template specialisation for properties of type double will need to take into account the precision of its UserPropertyDefinition, i.e., the number of digits to specify after the decimal point. This can be achieved by multiplying the value by a multiple of ten based on the precision, rounding the value (i.e., make it a whole number), and dividing by the same multiple of ten (you could specialise the value() function to do the division when the value is retrieved if you like). For example, for a precision of 2:
 * value = std::round(newValue * 100) / 100;
 *
 * The multiple of 10 can be determine by: 10p where ‘p’ is the precision value defined on the UserPropertyDefinition of the UserProperty.
 */
template <class T>
class TypedUserProperty : public UserProperty
{

    /**
     * @brief definition
     * a reference to the UserPropertyDefintion that defines the 'type' of this UserProperty.
     */
    std::shared_ptr<UserPropertyDefinition> definition;
    /**
     * @brief value
     * the underlying value of the (Typed)UserProperty. 'T' is the template parameter.
     */
    T _value;
    /**
     * @brief name
     * the name of the property; must match its UserPropertyDefinition
     */
    QString name;

    QString id;

public:
    TypedUserProperty(QString id, std::shared_ptr<UserPropertyDefinition> definition);
    TypedUserProperty(std::shared_ptr<UserPropertyDefinition> definition);
    TypedUserProperty() = default;
    TypedUserProperty(TypedUserProperty &);
    TypedUserProperty operator=(TypedUserProperty &);
    /**
     * @brief getValue
     * value of property
     * @return
     * value of property
     */
     QVariant value() override;
     /**
      * @brief getValue
      * gets value of class
      * @return
      * value
      */
     T getValue();


     /**
      * @brief setValue
      * set value to property
      * @param val
      * value to set to property
      * @return
      * true - successfully set value
      * false - invalid value
      */
     void setValue(QVariant val) override;



     /**
      * @brief setValue
      * do not set value
      * @param val
      * value to set
      */
     void setValue (T val);
     /**
      * @brief validate
      * @return
      */
     bool validate();
     /**
      * @brief setName
      * @param name
      */
     void setName(QString name);
     /**
      * @brief getName
      * fetches name of typedUserValidator
      * @return
      * name of validator
      */
     QString getName();

     QString getId();
     QString getErrorMessage();



};
}


#include "typeduserproperty.cpp"



#endif // TYPEDUSERPROPERTY_H
