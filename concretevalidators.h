#ifndef CONCRETEVALIDATORS_H
#define CONCRETEVALIDATORS_H

#include "userpropertyvalidator.h"
#include <QChar>
#include <QVector>

namespace core {
/**
 * @brief The MinimumValueValidator class
 * check the minimum value is valid
 * works for both int and double
 */
class MinimumValueValidator : public UserPropertyValidator{


    double min; // easy to compare double with int

    /**
     * @brief failMessage
     * holds the fail message to send to user
     */
    QString failMessage;
    /**
     * @brief value
     * checks if an int value is equal to above minimum value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (int val);
    /**
     * @brief value
     * checks if an double value is equal to above minimum value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (double val);

public:

    MinimumValueValidator(int val);

    MinimumValueValidator(double val);
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
    bool operator()( UserProperty &userProperty) override;


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
    QString failureMessage( UserProperty &property) override;

};
/**
 * @brief The MaximumValueValidator class
 * checks if value is below or equal to maximum value
 */
class MaximumValueValidator: public UserPropertyValidator {

    double max;

    /**
     * @brief failMessage
     * holds the fail message to send to user
     */
    QString failMessage;
    /**
     * @brief value
     * checks if an int value is equal to or below maximum value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (int val);
    /**
     * @brief value
     * checks if an double value is equal to or below maximum value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (double val);

public:
    MaximumValueValidator(double val);
    MaximumValueValidator(int val);
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
    bool operator()(UserProperty &userProperty) override;


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
    QString failureMessage( UserProperty &property) override;
};

/**
 * @brief The ValueListValidator class
 *
 */
class ValueListValidator : public UserPropertyValidator
{


    enum types {Int,Double,Qstring};

    types dataType;

    QVector<QString> strings;
    QVector<int> ints;
    QVector<double> doubles;

    /**
     * @brief failMessage
     * holds the fail message to send to user
     */
    QString failMessage;
    /**
     * @brief value
     * checks if an int value is a vali value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (int val);
    /**
     * @brief value
     * checks if an double value is a valid value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (double val);

    /**
     * @brief value
     * checks if a QString value is a valid value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (QString val);

public:

    explicit ValueListValidator(std::vector<double> val,QObject *parent = nullptr);
     explicit ValueListValidator(std::vector<int> val,QObject *parent = nullptr);
    explicit ValueListValidator(std::vector<QString> val,QObject *parent = nullptr);
     ValueListValidator(QVector<double> val);
     ValueListValidator(QVector<int> val);
     ValueListValidator(QVector<QString> val);
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
    bool operator()(UserProperty &userProperty) override;


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
    QString failureMessage( UserProperty &property) override;
};
/**
 * @brief The DepartmentValidator class
 * checks if the department value is a valid value
 * has only three valid values of QString anyway
 * "Maintenance", "Operations", "Logistics"
 */
class DepartmentValidator : public UserPropertyValidator
{

    /**
     * @brief failMessage
     * holds the fail message to send to user
     */
    QString failMessage;
    /**
     * @brief value
     * checks if an int value is a vali value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (int val);
    /**
     * @brief value
     * checks if an double value is a valid value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (double val);

    /**
     * @brief value
     * checks if a QString value is a valid value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (QString val);

public:
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
    bool operator()(UserProperty &userProperty) override;


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
    QString failureMessage(UserProperty &property) override;
};
/**
 * @brief The PhoneNumberValidator class
 * checks for a valid phone number
 *
 * constraints:
 * 8-11 digits (inclusive)
 * optional '+' at the beginning (and only the beginning)
 * Spaces are allowed
 * No other characters are all allowed
 * This allows values such as: 83026611, 8302 6611, 08 8302 6611, +61 8 8302 6611
 * But NOT: 8302, 8302 6611 12345, 61+ 8 8302 6611, ext. 25000
 */
class PhoneNumberValidator : public UserPropertyValidator
{

    /**
     * @brief validValue
     * checks if value is valid, allowed in number
     * @param i
     * value to check
     * @return
     * true - correct value
     * false - dissallowed value
     */
    bool validValue (const QChar i) const;
    /**
     * @brief failMessage
     * holds the fail message to send to user
     */
    QString failMessage;
    /**
     * @brief value
     * checks if an int value is a vali value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (int val);
    /**
     * @brief value
     * checks if an double value is a valid value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (double val);

    /**
     * @brief value
     * checks if a QString value is a valid value
     * @param val
     * value to check
     * @return
     * true - successful value
     * false - invalid value
     */
    bool value (QString val);

public:

    explicit PhoneNumberValidator(QString val,QObject *parent = nullptr);
    explicit PhoneNumberValidator(QString val);
    PhoneNumberValidator();
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
    bool operator()(UserProperty &userProperty) override;


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
    QString failureMessage( UserProperty &property) override;
};

}



#endif // CONCRETEVALIDATORS_H
