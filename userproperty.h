#ifndef USERPROPERTY_H
#define USERPROPERTY_H



#include <QObject>
#include <QVariant>
#include <tuple>


namespace core {

class UserProperty : public QObject
{

    /**
     * @brief name
     * the name of the property; must match its UserPropertyDefinition
     */
    QString name;

    Q_OBJECT
public:
    explicit UserProperty(QObject *parent = nullptr);
    //explicit UserProperty(std::shared_ptr<UserPropertyDefinition>,QObject *parent = nullptr);
    UserProperty(UserProperty &);
    /**
     * @brief UserProperty
     * since the class is derived from QObject,
     * it should have the common QObject constructor for specifying the parent object to support
     * Qt's object hierarchy; however, it also needs to be associated with the definition that is it 'type'.
     * @param definition
     * @param parent
     */
    /* since this is a virtual class there is no need to instantiate this constructor */
    // UserProperty(std::shared_ptr<UserPropertyDefinition> definition, QObject *parent);

    /**
     * @brief value
     * Retrieve/set the value of the property using a QVariant object. These functions are pure virtual at this level.
     * The stored value MUST NOT be changed after the completion of setValue(...) if validation fails on the given new value.
     * @note : QVariant has implicit constructors, so it is often unnecessary to create a QVariant object explicitly.
     * @return
     * QVariant value
     */
    virtual QVariant value() = 0;
    /**
     * @brief setValue
     * @param value
     */
    virtual void setValue(QVariant value) = 0;
    /**
     * @brief validate
     * validate whether the property’s value is correct with respect to the validators
     * stored on the associated UserPropertyDefinition: returns true if validation is successful,
     * false if any of he validators do not pass.
     * @return
     *
     * true - if validation successful
     * false - validators do no pass
     */
    bool validate();

    /**
     * @brief getName
     * gets name of property
     * @return
     */
    QString getName() const;



signals:
    /**
     * @brief valueChanged
     * emitted when the value of the property changes; MUST NOT be emitted
     * if validation fails and the value is reverted. Note: when a slot is executed
     * from a signal, the function sender() can be called to return a pointer to the sending object,
     * which would be a UserProperty for receivers of this signal.
     * @param newValue
     * @param oldValue
     */
     void valueChanged(QVariant newValue, QVariant oldValue);
     /**
     * @brief validationFailed
     * emitted when the validation of the value fails.
     * It MUST provide a message to indicate what the error is (which should be generated by the UserPropertyValidator).
     * @param errorMessage
     */
    void validationFailed(QString errorMessage);

public slots:
};
}

#endif // USERPROPERTY_H
