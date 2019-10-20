#ifndef REGISTEREDENTITY_H
#define REGISTEREDENTITY_H

#include <QObject>
#include <QDateTime>
namespace core {
class RegisteredEntity : public QObject
{


    Q_OBJECT

protected:
    /**
     * @brief id
     * the unique identifier of the entity, used to store and retrieve entities in the register.
     * Cannot be modified after the entity is created.
     */
    QString id;

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
protected:
    /**
       * @brief RegisteredEntity
       * since the class is derived from QObject, it should have the common
       * QObject constructor for specifying the parent object to support Qt's
       * object hierarchy; however, it also needs a unique identifier to be provided.
       * It must be protected to prevent direct instantiation.
       * @param id
       * identification of entity
       * @param parent
       * object parent
       */
    RegisteredEntity( QString id, QObject *parent = nullptr);
public:
    explicit RegisteredEntity(QObject *parent = nullptr);

    /*
     * Mutators and accessors
     *
     * */
    /**
       * @brief setDateTime
       * sets the latest date time
       * @param date
       * date to set otherwise use current date
       * @return
       * true - successfully set date time
       * false - invalid datetime
       */
      virtual bool setDateTime(QDateTime date = QDateTime::currentDateTime()) = 0;
    /**
       * @brief setLastEditedBy
       * set the last time user was edited
       * @param username
       * name of last user
       * @return
       * true - successfully set user
       * false - invalid user
       */
      virtual bool setLastEditedBy(QString username) = 0;
    /**
     * @brief getId
     * fetches entities id
     * @return
     *  entities id
     */
   virtual QString getId () = 0;


signals:

public slots:
};

}

#endif // REGISTEREDENTITY_H
