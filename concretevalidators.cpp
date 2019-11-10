#include "concretevalidators.h"
#include <QVariant>

using namespace core;

/*
 *
 * Minimum Value Validator
 *
 *
 *
 *
 *
 *
 *
 *
 * */

MinimumValueValidator::MinimumValueValidator(int val) {
    this->min = (double)val;


}


MinimumValueValidator::MinimumValueValidator(double val) {
    this->min = val;
}

bool MinimumValueValidator::operator()(UserProperty &property) {
    // no reason to determine type, as long as its double or integer its fine
    QVariant value = property.value();
    return (value >= min);

}

QString MinimumValueValidator::failureMessage(UserProperty &property) {
    QVariant value = property.value();
    std::string minstr = "Value has a minimum of "+ std::to_string(min) + ". You gave: ";
    if (this->operator()(property) == false)
        return QString::fromStdString(minstr)+value.toString();
    else {
        return "";
    }
}


/*
 *
 * Maximum Value Validator
 *
 *
 *
 *
 *
 *
 *
 *
 * */
MaximumValueValidator::MaximumValueValidator(int val) {
    this->max = (double)val;

}

MaximumValueValidator::MaximumValueValidator(double val) {
    this->max = val;
}

bool MaximumValueValidator::operator()(UserProperty &property) {
    // no reason to determine type, as long as its double or integer its fine
    QVariant value = property.value();
    return (value <= max);

}

QString MaximumValueValidator::failureMessage(UserProperty &property) {
    QVariant value = property.value();
    std::string minstr = "Value has a max of "+ std::to_string(max) + ". You gave: ";
    if (this->operator()(property) == false)
        return QString::fromStdString(minstr)+value.toString();
    else {
        return "";
    }
}

/*
 * ValueListValidator
 *
 *
 *
 *
 *
 * */

ValueListValidator::ValueListValidator (QVector<double> val) {
    dataType = Double;
    this->doubles = val;
}

ValueListValidator::ValueListValidator (QVector<QString> val) {
    dataType = Qstring;
    this->strings = val;
}
ValueListValidator::ValueListValidator (QVector<int> val) {
    dataType = Int;
    this->ints = val;
}

bool ValueListValidator::operator()(UserProperty &property) {
    if (dataType == Qstring)
        return value(property.value().toString());
    else if (dataType == Int)
        return value(property.value().toInt());
    else {
        return value(property.value().toDouble());
    }

}

bool ValueListValidator::value(QString val) {
    for (auto a : strings) {
        if (a.compare(val) == val)
            return true;
    }
    return false;
}

bool ValueListValidator::value(int val) {
    for (auto a : ints) {
        if (a == val)
            return true;
    }
    return false;
}

bool ValueListValidator::value(double val) {
    for (double a : doubles) {
        if (a == val)
            return true;
    }
    return false;
}


QString ValueListValidator::failureMessage(UserProperty &property) {
    QVariant value = property.value();
    QString minstr = QString("Your value does not meet expected values. Your value: "+value.toString());

    if (this->operator()(property) == false)
        return minstr;
    else {
        return "";
    }
}
/*
 *
 *
 *
 * Department Validator
 *
 *
 *
 * */

bool DepartmentValidator::operator()(UserProperty &property) {
    // no reason to determine type, as long as its double or integer its fine
    QVariant val = property.value();
    return this->value(val.toString());

}

bool DepartmentValidator::value(QString val) {
    if (val.compare("Maintenance") == 0)
        return true;
    else if (val.compare("Logistics") == 0)
        return true;
    else if (val.compare("Operations") == 0)
        return true;
    else {
        return false;
    }
}

QString DepartmentValidator::failureMessage(UserProperty &property) {
    QVariant value = property.value();
    QString minstr = QString("Department only allows Maintenance, Logistics or Operations. You Gave " +value.toString());
    if (this->operator()(property) == false)
        return minstr;
    else {
        return "";
    }
}
/*
 * Phone Validator functions
 *
 *
 *
 *
 *
 *
 *
 *
 * */
PhoneNumberValidator::PhoneNumberValidator() {

}
bool PhoneNumberValidator::validValue (const QChar i) const {
     char validValues[] = {'0','1','2','3','4','5','6','7','8','9',' ','\0'};

     for (char a : validValues) {
        if (i == a)
            return true;
     }
     return false;
}

// chose not to use regex
// don't know how to create proper error message
bool PhoneNumberValidator::value(QString val) {
    int spaces = 0;
    for (int i = 0 ; i < val.size();i++) {
        //check first value is a +
        if (val.at(i)  == '+') {
            if (i != 0) {
                this->failMessage = QString::fromStdString("A phone number can only have 0,1,2,3,4,5,6,7,8,9,[space], and a '+' at the beginning.You have "+val.toStdString());
                return false;
            }
        }else if (val.at(i)  == ' ') {
            spaces++; // count spaces to check for invalid length
        } else {
            // check if the rest of the values are valid
            if (!validValue(val.at(i))) {
                this->failMessage = QString::fromStdString("A phone number can only have 0,1,2,3,4,5,6,7,8,9,[space], and a '+' at the beginning.You have "+val.toStdString());
                return false;
            }
        }
    }

    if ((val.size() - spaces) < 8  && (val.size() - spaces) > 11)
        this->failMessage = QString::fromStdString("A phone number can only be between 8 and 11 digits long and have a '+' at the beginning.You have "+val.toStdString());

    return true;

}


bool PhoneNumberValidator::operator()(UserProperty &userProperty) {
        return value(userProperty.value().toString());
}

QString PhoneNumberValidator::failureMessage(UserProperty &property) {
    value(property.value().toString());
    return failMessage;
}
