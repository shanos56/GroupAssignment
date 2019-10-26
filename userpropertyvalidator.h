#ifndef USERPROPERTYVALIDATOR_H
#define USERPROPERTYVALIDATOR_H
#include "userproperty.h"

namespace core{
/**
 * @brief The UserPropertyValidator class
 * The UserPropertyValidator class is very simple.
 * It is a functor (i.e., a class that overloads the function call operator '()')
 * and takes part in an instance of the Strategy pattern: the context is the UserPropertyDefinition/UserProperty
 * classes and the concrete strategies are the specific types of validation that can be performed,
 * such as: minimum values, maximum value, enumeration, etc.
 */
class UserPropertyValidator
{
public:
    UserPropertyValidator();
    virtual ~UserPropertyValidator();
    /**
     * @brief operator ()
     * the overloaded function call '()' operator making UserPropertyValidator a functor. The overloaded operator takes a UserProperty (reference) and
     * returns true if the value of the property conforms to the validation criteria encapsulated by the validator object.
     * @param property
     * property to check if meets minimum standard
     * @return
     * true - meets minimum standard
     * false - fails to meet standard
     */
    virtual bool operator()(UserProperty &property) = 0;
    /**
     * @brief failureMessage
     * returns a failure message for the given UserProperty.
     * It takes the whole property so that the message may be constructed from as much information as required.
     * For example, a minimum value constraint violation may report:
     *      “The property ‘<name>’ must be greater than <min>. Value was <value>.”
     *
     * where <name> is the name of the property, <min> is the minimum value allowed by the validator,
     * and <value> is the value retrieved from the UserProperty.
     *
     * @param property
     * the property to check for failure message
     * @return
     * string containing failure message
     */
    virtual QString failureMessage( UserProperty &property) = 0;

};
}
#endif // USERPROPERTYVALIDATOR_H
